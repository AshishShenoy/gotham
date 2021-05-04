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

propagating_constants = {}

propagating_variables = {}

variable_info = {}


def preprocess_code(code):
    nd_code = code.split("\n")
    quad_code = list(map(lambda line: line.split(), nd_code))
    return quad_code


def fold_constants(code):
    op_code = []
    for instr in code:
        is_constant_folded = False
        if len(instr) > 1:
            if instr[1] in const_folding_operations:
                try:
                    a = int(instr[2])
                    b = int(instr[3])

                    constant = int(eval(f"{a}{const_folding_operations[instr[1]]}{b}"))
                    op_code.append([instr[0], "ASSIGN", str(constant), instr[4]])
                    is_constant_folded = True
                except ValueError:
                    pass

        if not is_constant_folded:
            op_code.append(instr)

    return op_code


def propagate_constants(code):
    op_code = []
    for instr in code:
        if len(instr) > 1:
            if instr[1] == "ASSIGN":
                try:
                    constant = int(instr[2])
                    propagating_constants[instr[3]] = constant
                    op_code.append(instr)
                    continue
                except ValueError:
                    if instr[3] in propagating_constants:
                        propagating_constants.pop(instr[3])

            if instr[2] in propagating_constants:
                instr[2] = str(propagating_constants[instr[2]])

            if len(instr) > 4:
                if instr[3] in propagating_constants:
                    instr[3] = str(propagating_constants[instr[3]])

        op_code.append(instr)

    return op_code


def propagate_variables(code):
    op_code = []
    for instr in code:
        if len(instr) > 1:
            if instr[1] == "ASSIGN":
                try:
                    src = int(instr[2])
                except:
                    instr[2] = propagating_variables.get(instr[2], instr[2])
                    try:
                        dest = int(instr[3])
                    except:
                        instr[3] = propagating_variables.get(instr[3], instr[3])
                        propagating_variables[instr[3]] = instr[2]
            else:
                instr[2] = propagating_variables.get(instr[2], instr[2])
                instr[3] = propagating_variables.get(instr[3], instr[3])

        op_code.append(instr)

    return op_code


def eliminate_dead_code(code):
    op_code = []

    for instr in code:
        if len(instr) > 1:
            dest_var = instr[-1]
            if dest_var not in variable_info:
                variable_info[dest_var] = {"is_dead": True}
            src_vars = []
            src_vars.append(instr[2])
            if len(instr) > 4:
                src_vars.append(instr[3])

            for var in src_vars:
                if var in variable_info:
                    variable_info[var]["is_dead"] = False

    for instr in code:
        if len(instr) > 1:
            dest_var = instr[-1]
            if not variable_info[dest_var]["is_dead"]:
                op_code.append(instr)

    return op_code


def stringify_code(code):
    nd_code = map(lambda line: "\t".join(line), code)
    complete_code = reduce(lambda a, b: "\n".join([a, b]), nd_code, "")
    return complete_code


def main():
    code : str
    with open("icg.txt", "r+") as f:
        code = preprocess_code(f.read())

        optimizations = [
            fold_constants,
            propagate_constants,
            propagate_variables,
            eliminate_dead_code,
        ]

    
        for optimize_function in optimizations:
            with open("before_optimization.txt", "w") as bf:
                bf.write(stringify_code(code))
            code = optimize_function(code)
    
    with open("icg.txt", "w") as f:
        f.write(stringify_code(code))

if __name__ == "__main__":
    main()
