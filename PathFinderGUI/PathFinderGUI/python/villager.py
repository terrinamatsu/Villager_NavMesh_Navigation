class Villager():
  """ A Villager """

  def __init__(self, needs, age):
    """
      needs: array containing integer values for
                  Hunger
                  Thirst
                  Sleep
                  Social
                  Hygiene
                  Liquids
                  Solids
                  Fun
                  Fulfillment
      age: integer value age in days.

    """
    a  = 1

  ####################################
  #   Needs Calculations
  ####################################
  def hungerCalc(self, currentTime) -> int:
    """ Calculate hunger, with base hunger level (10),
        plus three peaks around each meal time. """
    # Base level + traits
    hunger= 10 + (20 * (self.traits[a.traits['Always Hungry']] - self.traits[a.traits['Never Hungry']]))
    # CurrentAction + Random Offset
    hunger -= self.currentAction.data.needsFulfill_Sec[0] - random.randint(0,20)
    # Peaks before each meal time
    if ((currentTime < 420) and (currentTime > 120)):
        hunger -= (1/80) * (currentTime - 270) * (currentTime - 270) - 290
    elif ((currentTime < 720) and (currentTime > 420)):
        hunger -= (1/80) * (currentTime - 570) * (currentTime - 570) - 290
    elif ((currentTime < 1020) and (currentTime > 720)):
        hunger -= (1/80) * (currentTime - 870) * (currentTime - 870) - 290

    return int(hunger)

  def thirstCalc(self) -> int:
    return 240 - self.currentAction.data.needsFulfill_Sec[1] + random.randint(0,50)

  def fatigueCalc(self, currentTime) -> int:
    # Base Level & Traits
    fatigue = 2  - self.currentAction.data.needsFulfill_Sec[2] + random.randint(0,5)
    # Peak before bed @ 10pm
    if (currentTime <= 1320) and (currentTime > 900):
        timeTemp = currentTime - 900
        fatigue += (6 * timeTemp)/5 + (0.00170659 * timeTemp * timeTemp) - (0.00001107 * timeTemp * timeTemp * timeTemp)
    return int(fatigue)
    #-250*(2*(1/1200 * currentTime)*(1/1200 * currentTime)*(1/1200 * currentTime)-3*(1/1200 * currentTime)*(1/1200 * currentTime)) - ((1/5) * currentTime)

  def socialCalc(self) -> int:
    return 360 + int((self.personality[0] / 4)-25) - self.currentAction.data.needsFulfill_Sec[3] + random.randint(0,50)

  def hygieneCalc(self) -> int:
    return 60 - self.currentAction.data.needsFulfill_Sec[4] + random.randint(0,50)

  def bladderCalc(self) -> int:
    return 360 + (20 * self.traits[a.traits['Tiny Bladder']]) - (20 * self.traits[a.traits['Steel Bladder']]) - self.currentAction.data.needsFulfill_Sec[5] + random.randint(0,50)

  def solidsCalc(self) -> int:
    return 300 + (20 * self.traits[a.traits['Tiny Bladder']]) - (20 * self.traits[a.traits['Steel Bladder']]) - self.currentAction.data.needsFulfill_Sec[6] + random.randint(0,50)

  def funCalc(self) -> int:
    return 200 + (20 * self.traits[a.traits['Dopamine Junkie']]) - self.currentAction.data.needsFulfill_Sec[7] + random.randint(0,50)

  def fulfillmentCalc(self) -> int:
    return 100 + (20 * self.traits[a.traits['Motivated']]) - (20 * self.traits[a.traits['Procrastinator']]) - self.currentAction.data.needsFulfill_Sec[8] + random.randint(0,50)

