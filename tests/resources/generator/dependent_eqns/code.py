from math import *


def initialize_constants(states, variables):
    states[0] = 0.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = 1.0


def compute_variables(voi, states, rates, variables):
    variables[0] = 2.0*voi
    variables[1] = 3.0*variables[0]

