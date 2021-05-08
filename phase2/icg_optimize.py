from functools import reduce


const_folding_operations = {
    "ADD": "+",
    "SUB": "-",
    "MUL": "*",
    "DIV": "/",
    "MOD": "%",
    "OR": "or",
    "AND": "and",
}


# Convert string into a list of instructions, with each instruction
# split into its fields.
def preprocess_code(code):
    nd_code = code.split("\n")
    quad_code = list(map(lambda line: line.split(), nd_code))
    return quad_code


# Checks if a string can be safely converted to an integer.
def is_integer(string):
    try:
        int(string)
        return True
    except:
        return False


# Performs constant folding by replacing arithmetic operations on
# constants with constant assignments.
# Does not change the number of instructions.
def fold_constants(code):
    op_code = []
    for instr in code:
        if len(instr) > 1:
            if instr[1] in const_folding_operations:
                if is_integer(instr[2]) and is_integer(instr[3]):
                    a = int(instr[2])
                    b = int(instr[3])

                    constant = int(eval(f"{a}{const_folding_operations[instr[1]]}{b}"))
                    op_code.append([instr[0], "ASSIGN", str(constant), instr[4]])
                    continue

        op_code.append(instr)

    return op_code


# Performs constant propagation by replacing the instances of
# variables whose values are known to be a constant, with the
# constant value.
# Does not change the number of instructions.
def propagate_constants(code):
    op_code = []

    propagating_constants = {}

    for instr in code:
        if len(instr) > 1:
            if instr[1] == "ASSIGN":
                if is_integer(instr[2]):
                    constant = int(instr[2])
                    propagating_constants[instr[3]] = constant
                    op_code.append(instr)
                    continue
                else:
                    if instr[3] in propagating_constants:
                        propagating_constants.pop(instr[3])
            
            if instr[2] in propagating_constants:
                instr[2] = str(propagating_constants[instr[2]])

            if len(instr) > 4:
                if instr[3] in propagating_constants:
                    instr[3] = str(propagating_constants[instr[3]])

        op_code.append(instr)

    return op_code


# Performs copy propagation by replacing instances of variables that
# are references to other variables, with the referenced variable.
# Does not change the number of instructions.
def propagate_variables(code):
    op_code = []

    propagating_variables = {}

    for instr in code:
        if len(instr) > 1:
            if instr[1] == "ASSIGN":
                if not is_integer(instr[2]):
                    instr[2] = propagating_variables.get(instr[2], instr[2])
                    if not is_integer(instr[3]):
                        instr[3] = propagating_variables.get(instr[3], instr[3])
                        propagating_variables[instr[3]] = instr[2]
            else:
                instr[2] = propagating_variables.get(instr[2], instr[2])

                if len(instr) > 4:
                    instr[3] = propagating_variables.get(instr[3], instr[3])

        op_code.append(instr)

    return op_code


# Performs dead code removal through the following steps:
# 1. Compute list of printed variables (only side effect present)
# 2. Compute all variables that the printed variables depend on.
#    These variables are treated as 'alive', i.e. it is required for
#    the program's effects.
# 3. Remove all other instructions that have a different destination
#    variable.
def eliminate_dead_code(code):
    op_code = []

    print_variables = set()

    for instr in code:
        if len(instr) > 1 and instr[1] == "PARAMS":
            if not is_integer(instr[2]):
                print_variables.add(instr[2])

    alive_variables = set(print_variables)
    old_alive_variables = set()

    while old_alive_variables != alive_variables:
        old_alive_variables = alive_variables
        for instr in code:
            if len(instr) > 1:
                dest_var = instr[-1]
                src_vars = instr[2:-1]

                if dest_var in alive_variables:
                    for var in src_vars:
                        if not is_integer(var):
                            alive_variables.add(var)

    for instr in code:
        if len(instr) > 1:
            if instr[-1] in alive_variables:
                op_code.append(instr)
            elif instr[1] in ["PARAMS", "CALL"]:
                op_code.append(instr)
        else:
            op_code.append(instr)

    return op_code


# Converts list of instructions back into a string for displaying.
def stringify_code(code):
    code = list(map(lambda line: line[1:], code))

    nd_code = map(lambda line: "\t".join(line), code)
    complete_code = reduce(lambda a, b: "\n".join([a, b]), nd_code, "")
    return complete_code[1:]


def main():
    with open("icg.txt", "r") as f:
        code = preprocess_code(f.read())

        optimizations = [
            fold_constants,
            propagate_constants,
            propagate_variables,
            eliminate_dead_code,
        ]

        with open("optimization_steps.txt", "w") as f:
            # Continue optimizations until code does not change.
            old_code = []
            while old_code != code:
                old_code = code
                for optimize_function in optimizations:
                    f.write(optimize_function.__name__ + "\n")
                    f.write(stringify_code(code))
                    f.write("\n")

                    code = optimize_function(code)

    with open("optimized_icg.txt", "w") as f:
        f.write(stringify_code(code))


if __name__ == "__main__":
    main()
