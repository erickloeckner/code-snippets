class State():
    def __init__(self):
        self.rules = {}
        
    def addrule(self, state, rule):
        self.rules[state] = rule

    def update(self):
        pass

    def draw(self):
        pass

class StateMachine():
    def __init__(self):
        self.current = None
        self.in_val = ''

    def update(self):
        if self.current == None:
            return
        for s, r in self.current.rules.items():
            if r():
                self.current = s
        self.current.update()

    def draw(self):
        if self.current == None:
            return
        self.current.draw()

sm = StateMachine()

def draw_title():
    print('STATE: title_screen')
    sm.in_val = input('type "y" to continue: ')

title_screen = State()
title_screen.draw = draw_title

def draw_game():
    print('STATE: game_screen')
    sm.in_val = input('type "q" to quit to title, "z" to end: ')

game_screen = State()
game_screen.draw = draw_game

title_screen.addrule(game_screen, lambda: sm.in_val == 'y')
game_screen.addrule(title_screen, lambda: sm.in_val == 'q')
sm.current = title_screen

while sm.in_val != 'z':
    sm.update()
    sm.draw()
