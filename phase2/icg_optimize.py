import sys
from functools import reduce
from pprint import pprint

const_folding_operations = {
    "ADD": "+",
    "SUB": "-",
    "MUL": "*",
    "DIV": " /",
    "MOD": "%",
    "OR": "or",
    "AND": "and",
}

variable_map = {}


def preprocess_code(code):
    nd_code = code.split("\n")
    quad_code = list(map(lambda line: line.split(), nd_code))
    return quad_code


def lookup_varmap(symbol):
    if symbol in variable_map:
        variable_map[symbol]["is_dead"] = False
        return str(variable_map[symbol]["value"])
    else:
        return symbol


def insert_varmap(symbol, field, value):
    if symbol in variable_map:
        variable_map[symbol][field] = value
    else:
        variable_map[symbol] = {}
        variable_map[symbol][field] = value
        variable_map[symbol]["is_dead"] = True


def fold_constants(instr):
    instr[2] = lookup_varmap(instr[2])
    instr[3] = lookup_varmap(instr[3])

    a = int(instr[2])
    b = int(instr[3])

    constant = eval(f"{a}{const_folding_operations[instr[1]]}{b}")
    insert_varmap(instr[4], "value", constant)


def propagate_constants(instr):
    instr[2] = lookup_varmap(instr[2])
    instr[3] = lookup_varmap(instr[3])

    return instr


def propagate_variable(instr):
    instr[2] = lookup_varmap(instr[2])
    insert_varmap(instr[3], "value", instr[2])
    
    return instr


def evaluate_expression(code):
    op_code = []
    for instr in code:
        if len(instr) > 1:
            if instr[1] in const_folding_operations:
                try:
                    fold_constants(instr)
                except:
                    instr = propagate_constants(instr)
                    op_code.append(instr)

            elif instr[1] == "ASSIGN":
                instr = propagate_variable(instr)
                op_code.append(instr)

            else:
                op_code.append(instr)

    return op_code


def eliminate_dead_code(code):
    op_code = []

    for instr in code:
        if len(instr) > 1 and instr[1] == "ASSIGN":
            if not variable_map[instr[3]]["is_dead"]:
                op_code.append(instr)

    return op_code


def stringify_code(code):
    nd_code = map(lambda line: "\t".join(line), code)
    complete_code = reduce(lambda a, b: "\n".join([a, b]), nd_code, "")
    return complete_code


def main():
    with open("icg.txt", "r") as f:
        code = preprocess_code(f.read())

        optimizations = [
            evaluate_expression,
            eliminate_dead_code,
        ]

        for optimize_function in optimizations:
            code = optimize_function(code)

        code = stringify_code(code)
        print(code)


if __name__ == "__main__":
    main()
