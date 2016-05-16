#basic interpreter mate

from sys import *

currentFile = ""
tokens = []
symbols = {}
constants = {}
functions = {}

class function:
    __name = ""
    __arguments = {}
    __symbols = {}
    __constants = {}
    __parent = ""
    __children = []

    def __init__(self, name, arguments=None, symbols=None, constants=None, parent=None, children=None):
        self.__name = name
        if arguments != None:
            self.__arguments = arguments
        if symbols != None:
            self.__symbols = symbols
        if constants != None:
            self.__constants = constants
        if parent != None:
            self.__parent = parent
        if children != None:
            self.__children = children

def open_file(filename):
    print("opening " + filename)
    data = open(filename, "r").read()
    data += "!!EOF!!"
    return data

def lex(filecontents):
    global tokens
    filecontents = list(filecontents)
    tok = ""
    expr = ""
    var = ""
    string = ""
    func = ""
    use = ""
    const = ""
    isexpr = 0
    state = 0
    varstarted = 0
    conststarted = 0
    funcstarted = 0
    namestarted = 0
    usestarted = 0
    for char in filecontents:
        tok += char
        if tok == " ":
            if state == 0:
                tok = ""
            else:
                tok = " "
        elif tok == "use":
            usestarted = 1
            use += tok
            tok = ""
        elif usestarted == 1:
            if tok == ";":
                if use != "":
                    if use[3:] + ".pxe" != currentFile:
                        newData = open_file(use[3:] + ".pxe")
                        tokens = tokens + lex(newData)
                        use = ""
                        usestarted = 0
                    else:
                        print("USE ERROR: can't import a file from itself")
                        exit()
            use += tok
            tok = ""
        elif tok == "\n" or tok == "!!EOF!!" or tok == "{" or tok == "&":
            if expr != "" and isexpr == 1:
                tokens.append("EXPR:" + expr)
                expr = ""
                isexpr = 0
            elif expr != "" and isexpr == 0:
                tokens.append("NUM:" + expr)
                expr = ""
            elif var != "" and varstarted == 1:
                tokens.append("VAR:" + var)
                varstarted = 0
                var = ""
            elif const != "" and conststarted == 1:
                tokens.append("CONST:" + const)
                conststarted = 0
                const = ""
            elif func != "" and funcstarted == 1:
                tokens.append("FUNC:" + func)
                if tok != "{":
                    tokens.append("PASS")
                funcstarted = 0
                func = ""
            elif use != "" and usestarted == 1:
                tokens.append("USE:" + use.replace("\n", ""))
                usestarted = 0
                use = ""
            if tok == "{":
                tokens.append("{")
            elif tok == "&":
                tokens.append("CONCAT")
            tok = ""
        elif tok == "=" and state == 0:
            if expr != "" and isexpr == 0:
                tokens.append("NUM:" + expr)
                expr = ""
            elif expr != "" and isexpr == 1:
                tokens.append("EXPR:" + expr)
                expr = ""
                isexpr = 0
            if var != "" and varstarted == 1:
                tokens.append("VAR:" + var)
                varstarted = 0
                var = ""
            elif const != "" and conststarted == 1:
                tokens.append("CONST:" + const)
                conststarted = 0
                const = ""
            if tokens[-1] == "EQUALS":
                if expr != "" and isexpr == 1:
                    tokens.append("EXPR:" + expr)
                    expr = ""
                    isexpr = 0
                tokens[-1] = "IS"
            elif tokens[-1] == "SMALLER":
                if expr != "" and isexpr == 1:
                    tokens.append("EXPR:" + expr)
                    expr = ""
                    isexpr = 0
                tokens[-1] = "SMALLERIS"
            elif tokens[-1] == "GREATER":
                if expr != "" and isexpr == 1:
                    tokens.append("EXPR:" + expr)
                    expr = ""
                    isexpr = 0
                tokens[-1] = "GREATERIS"
            else:
                tokens.append("EQUALS")
            tok = ""
        elif tok == "!=" and state == 0:
            if expr != "" and isexpr == 0:
                tokens.append("NUM:" + expr)
                expr = ""
            elif expr != "" and isexpr == 1:
                tokens.append("EXPR:" + expr)
                expr = ""
                isexpr = 0
            if var != "" and varstarted == 1:
                tokens.append("VAR:" + var)
                varstarted = 0
                var = ""
            elif const != "" and conststarted == 1:
                tokens.append("CONST:" + const)
                conststarted = 0
                const = ""
            tokens.append("NOT")
            tok = ""
        elif tok == "<" and state == 0:
            if expr != "" and isexpr == 0:
                tokens.append("NUM:" + expr)
                expr = ""
            elif expr != "" and isexpr == 1:
                tokens.append("EXPR:" + expr)
                expr = ""
                isexpr = 0
            if var != "" and varstarted == 1:
                tokens.append("VAR:" + var)
                varstarted = 0
                var = ""
            elif const != "" and conststarted == 1:
                tokens.append("CONST:" + const)
                conststarted = 0
                const = ""
            tokens.append("SMALLER")
            tok = ""
        elif tok == ">" and state == 0:
            if expr != "" and isexpr == 0:
                tokens.append("NUM:" + expr)
                expr = ""
            elif expr != "" and isexpr == 1:
                tokens.append("EXPR:" + expr)
                expr = ""
                isexpr = 0
            if var != "" and varstarted == 1:
                tokens.append("VAR:" + var)
                varstarted = 0
                var = ""
            elif const != "" and conststarted == 1:
                tokens.append("CONST:" + const)
                conststarted = 0
                const = ""
            tokens.append("GREATER")
            tok = ""
        elif tok == "var" and state == 0:
            varstarted = 1
            var += tok
            tok = ""
        elif tok == "const" and state == 0:
            conststarted = 1
            var += tok
            tok = ""
        elif varstarted == 1:
            if tok == "<" or tok == ">":
                if var != "":
                    tokens.append("VAR:" + var)
                    var = ""
                    varstarted = 0
            var += tok
            tok = ""
        elif conststarted == 1:
            if tok == "<" or tok == ">":
                if const != "":
                    tokens.append("CONST:" + const)
                    const = ""
                    conststarted = 0
            const += tok
            tok = ""
        elif tok == "func" and state == 0 and varstarted == 0:
            funcstarted = 1
            func += tok
            tok = ""
        elif funcstarted == 1:
            if tok == ";}":
                if func != "":
                    tokens.append("FUNC:" + func)
                    tokens.append(";}")
                    func = ""
                    funcstarted = 0
            func += tok
            tok = ""
        elif tok == "0" or tok == "1" or tok == "2" or tok == "3" or tok == "4" or tok == "5" or tok == "6" or tok == "7" or tok == "8" or tok == "9":
            expr += tok
            tok = ""
        elif tok == "+" or tok == "-" or tok == "*" or tok == "/":
            isexpr = 1
            expr += tok
            tok = ""
        elif tok == "print":
            tokens.append("PRINT")
            tok = ""
        elif tok == "input":
            tokens.append("INPUT")
            tok = ""
        elif tok == ";}":
            tokens.append(";}")
            tok = ""
        elif tok == "}":
            tokens.append("}")
            tok = ""
        elif tok == "pass" and varstarted == 0 and state == 0:
            tokens.append("PASS")
            tok = ""
        elif tok == "if":
            tokens.append("IF")
            tok = ""
        elif tok == "else":
            tokens.append("ELSE")
            tok = ""
        elif tok == "{":
            if expr != "" and isexpr == 0:
                tokens.append("NUM:" + expr)
                expr = ""
            tokens.append("{")
            tok = ""
        elif tok == "\t" and varstarted == 0:
            tok = ""
        elif tok == "\"" or tok == " \"":
            if state == 0:
                state = 1
            elif state == 1:
                tokens.append("STRING:" + string + "\"")
                string = ""
                tok = ""
                state = 0
        elif tok == "True" and state == 0:
            tokens.append("BOOL:" + tok)
            tok = ""
        elif tok == "False" and state == 0:
            tokens.append("BOOL:" + tok)
            tok = ""
        elif state == 1:
            string += tok
            tok = ""
        elif state == 0 and tok == "exit":
            tokens.append("EXIT")
            tok = ""
    #return ""
    print(tokens)
    return tokens

def assingVariable(varname, varvalue):
    symbols[varname] = varvalue

def assignConstant(constname, constvalue):
    if constname not in constants:
        constants[constname] = constvalue
    elif constname in constants:
        print("CONSTANT ERROR: constant with the name `" + constname + "` is already defined")
        exit()

def doFUNCTION(functionname, functionvalue):
    functions[functionname] = functionvalue

def getFUNCTION(functionname):
    if functionname in functions:
        return functions[functionname][1:-1]
    else:
        print("FUNCTION ERROR: undefined function " + functionname)
        exit()

def getVariable(varname):
    if varname in symbols:
        return symbols[varname]
    else:
        print("VARIABLE ERROR: undefined variable " + varname)
        exit()

def getConstant(constname):
    if constname in constants:
        return constants[constname]
    else:
        print("CONSTANT ERROR: undefined constant " + constname)
        exit()

def getINPUT(string, varname):
    i = input(string[1:-1] + " ")
    symbols[varname[3:]] = "STRING:" + "\"" + i + "\""

def parse(toks):
    i = 0
    prevState = 1
    loopStarted = 0
    funcToDo = ""
    funcToDo = []
    while(i < len(toks)):
        try:
            if toks[i] == "}":
                i+=1
            try:
                if toks[i] == "{":
                    i+=1
            except IndexError:
                break
            if toks[i] == "EXIT":
                exit()
            if toks[i][0:3] == "USE":
                print("use")
                newData = open_file(toks[i][7:] + ".pxe")
                newToks = lex(newData)
                i+=1
            elif toks[i][0:4] == "FUNC" and toks[i+1] == "{":
                funcToDoName = toks[i][9:]
                while(toks[i] != ";}"):
                    i+=1
                    if toks[i] == ";}":
                        funcToDo.append(toks[i])
                        doFUNCTION(funcToDoName, funcToDo)
                        funcToDo = []
                        funcToDoName = ""
                        break
                    funcToDo.append(toks[i])
                i+=1
            elif toks[i][0:4] == "FUNC" and toks[i+1] != "{":
                parse(getFUNCTION(toks[i][9:]))
                i+=2
            elif toks[i] == "PASS":
                i+=1
            elif toks[i][0:4] == "NAME":
                i+=1
            elif toks[i] == "PRINT":
                if toks[i] == "PRINT":
                    if toks[i+1][0:6] == "STRING":
                        print(toks[i+1][8:-1])
                    elif toks[i+1][0:3] == "NUM":
                        print(toks[i+1][4:])
                    elif toks[i+1][0:4] == "EXPR":
                        print(eval(toks[i+1][5:]))
                    elif toks[i+1][0:4] == "BOOL":
                        print(toks[i+1][5:])
                    elif toks[i+1][0:3] == "VAR":
                        if constants != {}:
                            varToPrint = getVariable(toks[i+1][12:])
                        elif constants == {}:
                            varToPrint = getVariable(toks[i+1][7:])
                        if varToPrint[0:6] == "STRING":
                            print(varToPrint[8:-1])
                        elif varToPrint[0:3] == "NUM":
                            print(varToPrint[4:])
                        elif varToPrint[0:4] == "BOOL":
                            print(varToPrint[5:])
                    elif toks[i+1][0:5] == "CONST":
                        constToPrint = getConstant(toks[i+1][6:])
                        if constToPrint[0:6] == "STRING":
                            print(constToPrint[8:-1])
                        elif constToPrint[0:3] == "NUM":
                            print(constToPrint[4:])
                        elif constToPrint[0:4] == "BOOL":
                            print(constToPrint[5:])
                i += 2
            elif toks[i][0:3] + " " + toks[i+1] == "VAR EQUALS":
                if toks[i+2][0:4] == "EXPR":
                    assingVariable(toks[i][7:], "NUM:" + str(eval(toks[i+2][5:])))
                elif toks[i+2][0:3] == "NUM":
                    assingVariable(toks[i][7:], toks[i+2])
                elif toks[i+2][0:6] == "STRING":
                    assingVariable(toks[i][7:], toks[i+2])
                elif toks[i+2][0:3] == "VAR":
                    assingVariable(toks[i][7:], getVariable(toks[i+2][7:]))
                elif toks[i+2][0:4] == "BOOL":
                    assingVariable(toks[i][7:], toks[i+2])
                elif toks[i+2][0:5] == "CONST":
                    assingVariable(toks[i][12:].replace("const", ""), getConstant(toks[i+2][6:]))
                i+=3
            elif toks[i][0:5] + " " + toks[i+1] == "CONST EQUALS":
                if toks[i+2][0:4] == "EXPR":
                    assignConstant(toks[i][6:], "NUM:" + str(eval(toks[i+2][5:])))
                elif toks[i+2][0:3] == "NUM":
                    assignConstant(toks[i][6:], toks[i+2])
                elif toks[i+2][0:6] == "STRING":
                    assignConstant(toks[i][6:], toks[i+2])
                elif toks[i+2][0:3] == "VAR":
                    assignConstant(toks[i][6:], getVariable(toks[i+2][12:]))
                elif toks[i+2][0:4] == "BOOL":
                    assignConstant(toks[i][6:], toks[i+2])
                elif toks[i+2][0:5] == "CONST":
                    assignConstant(toks[i][6:].replace("const", ""), getConstant(toks[i+2][6:]))
                i+=3
            elif toks[i] + " " + toks[i+1][0:6] == "INPUT STRING":
                if toks[i+2][0:3] == "VAR":
                    getINPUT(toks[i+1][7:], toks[i+2][4:])
                i+=3
            elif toks[i] + " " + toks[i+2] + " " + toks[i+4] == "IF IS {":
                if toks[i+1][0:3] == "NUM" and toks[i+3][0:3] == "NUM":
                    if toks[i+1][4:] == toks[i+3][4:]:
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:6] == "STRING" and toks[i+3][0:6] == "STRING":
                    if toks[i+1][8:-1] == toks[i+3][8:-1]:
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "VAR" and toks[i+3][0:3] == "VAR":
                    if getVARIABLE(toks[i+1][7:]) == getVARIABLE(toks[i+3][7:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "BOOL" and toks[i+3][0:4] == "BOOL":
                    if toks[i+1][5:] == toks[i+3][5:]:
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:4] == "EXPR":
                    if eval(toks[i+1][5:]) == eval(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:3] == "NUM":
                    t = eval(toks[i+1][6:])
                    if str(t) == str(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "NUM" and toks[i+3][0:4] == "EXPR":
                    t = eval(toks[i+1][5:])
                    if str(t) == str(toks[i+1][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:5] == "CONST" and toks[i+3][0:5] == "CONST":
                    if getConstant(toks[i+1][6:]) == getConstant(toks[i+3][6:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
            elif toks[i] + " " + toks[i+2] + " " + toks[i+4] == "IF NOT {":
                if toks[i+1][0:3] == "NUM" and toks[i+3][0:3] == "NUM":
                    if toks[i+1][4:] != toks[i+3][4:]:
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:6] == "STRING" and toks[i+3][0:6] == "STRING":
                    if toks[i+1][8:-1] != toks[i+3][8:-1]:
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "VAR" and toks[i+3][0:3] == "VAR":
                    if getVARIABLE(toks[i+1][7:]) != getVARIABLE(toks[i+3][7:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "BOOL" and toks[i+3][0:4] == "BOOL":
                    if toks[i+1][5:] != toks[i+3][5:]:
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:4] == "EXPR":
                    if eval(toks[i+1][5:]) != eval(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:3] == "NUM":
                    t = eval(toks[i+1][6:])
                    if str(t) != str(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "NUM" and toks[i+3][0:4] == "EXPR":
                    t = eval(toks[i+1][5:])
                    if str(t) != str(toks[i+1][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:5] == "CONST" and toks[i+3][0:5] == "CONST":
                    if getConstant(toks[i+1][6:]) != getConstant(toks[i+3][6:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
            elif toks[i] + " " + toks[i+2] + " " + toks[i+4] == "IF GREATERIS {":
                if toks[i+1][0:3] == "NUM" and toks[i+3][0:3] == "NUM":
                    if int(toks[i+1][4:]) >= int(toks[i+3][4:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:6] == "STRING" and toks[i+3][0:6] == "STRING":
                    if toks[i+1][8:-1] >= toks[i+3][8:-1]:
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "VAR" and toks[i+3][0:3] == "VAR":
                    if getVARIABLE(toks[i+1][7:]) >= getVARIABLE(toks[i+3][7:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:5] == "CONST" and toks[i+3][0:5] == "CONST":
                    if getConstant(toks[i+1][6:]) >= getConstant(toks[i+3][6:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "BOOL" and toks[i+3][0:4] == "BOOL":
                    print("ILLEGAL OPERATION ON TYPE BOOLEAN: you can't compare the size of booleans with each other")
                    exit()
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:4] == "EXPR":
                    if eval(toks[i+1][5:]) >= eval(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:3] == "NUM":
                    t = eval(toks[i+1][6:])
                    if int(t) >= int(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "NUM" and toks[i+3][0:4] == "EXPR":
                    t = eval(toks[i+1][5:])
                    if int(t) >= int(toks[i+1][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
            elif toks[i] + " " + toks[i+2] + " " + toks[i+4] == "IF SMALLERIS {":
                if toks[i+1][0:3] == "NUM" and toks[i+3][0:3] == "NUM":
                    if int(toks[i+1][4:]) <= int(toks[i+3][4:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:6] == "STRING" and toks[i+3][0:6] == "STRING":
                    if toks[i+1][8:-1] <= toks[i+3][8:-1]:
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "VAR" and toks[i+3][0:3] == "VAR":
                    if getVARIABLE(toks[i+1][7:]) <= getVARIABLE(toks[i+3][7:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:5] == "CONST" and toks[i+3][0:5] == "CONST":
                    if getConstant(toks[i+1][6:]) <= getConstant(toks[i+3][6:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "BOOL" and toks[i+3][0:4] == "BOOL":
                    print("ILLEGAL OPERATION ON TYPE BOOLEAN: you can't compare the size of booleans with each other")
                    exit()
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:4] == "EXPR":
                    if eval(toks[i+1][5:]) <= eval(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:3] == "NUM":
                    t = eval(toks[i+1][6:])
                    if int(t) <= int(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "NUM" and toks[i+3][0:4] == "EXPR":
                    t = eval(toks[i+1][5:])
                    if int(t) <= int(toks[i+1][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
            elif toks[i] + " " + toks[i+2] + " " + toks[i+4] == "IF SMALLER {":
                if toks[i+1][0:3] == "NUM" and toks[i+3][0:3] == "NUM":
                    if int(toks[i+1][4:]) < int(toks[i+3][4:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:6] == "STRING" and toks[i+3][0:6] == "STRING":
                    if toks[i+1][8:-1] < toks[i+3][8:-1]:
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "VAR" and toks[i+3][0:3] == "VAR":
                    if getVARIABLE(toks[i+1][7:]) < getVARIABLE(toks[i+3][7:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:5] == "CONST" and toks[i+3][0:5] == "CONST":
                    if getConstant(toks[i+1][6:]) < getConstant(toks[i+3][6:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "BOOL" and toks[i+3][0:4] == "BOOL":
                    print("ILLEGAL OPERATION ON TYPE BOOLEAN: you can't compare the size of booleans with each other")
                    exit()
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:4] == "EXPR":
                    if eval(toks[i+1][5:]) < eval(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:3] == "NUM":
                    t = eval(toks[i+1][6:])
                    if int(t) < int(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "NUM" and toks[i+3][0:4] == "EXPR":
                    t = eval(toks[i+1][5:])
                    if int(t) < int(toks[i+1][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
            elif toks[i] + " " + toks[i+2] + " " + toks[i+4] == "IF GREATER {":
                if toks[i+1][0:3] == "NUM" and toks[i+3][0:3] == "NUM":
                    if int(toks[i+1][4:]) > int(toks[i+3][4:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:6] == "STRING" and toks[i+3][0:6] == "STRING":
                    if toks[i+1][8:-1] > toks[i+3][8:-1]:
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "VAR" and toks[i+3][0:3] == "VAR":
                    if getVARIABLE(toks[i+1][7:]) > getVARIABLE(toks[i+3][7:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:5] == "CONST" and toks[i+3][0:5] == "CONST":
                    if getConstant(toks[i+1][6:]) > getConstant(toks[i+3][6:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "BOOL" and toks[i+3][0:4] == "BOOL":
                    print("ILLEGAL OPERATION ON TYPE BOOLEAN: you can't compare the size of booleans with each other")
                    exit()
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:4] == "EXPR":
                    if eval(toks[i+1][5:]) > eval(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:3] == "NUM":
                    t = eval(toks[i+1][6:])
                    if int(t) > int(toks[i+3][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "NUM" and toks[i+3][0:4] == "EXPR":
                    t = eval(toks[i+1][5:])
                    if int(t) > int(toks[i+1][5:]):
                        i+=5
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
            elif toks[i] + " " + toks[i+1][0:4] + " " + toks[i+2] + " " + toks[i+3][0:4] + " " + toks[i+4] == "WHILE BOOL IS BOOL {" or toks[i] + " " + toks[i+1][0:3] + " " + toks[i+2] + " " + toks[i+3][0:3] + " " + toks[i+4] == "WHILE NUM IS NUM {" or toks[i] + " " + toks[i+1][0:3] + " " + toks[i+2] + " " + toks[i+3][0:3] + " " + toks[i+4] == "WHILE VAR IS VAR {" or toks[i] + " " + toks[i+1][0:6] + " " + toks[i+2] + " " + toks[i+3][0:6] + " " + toks[i+4] == "WHILE STRING IS STRING {" or toks[i] + " " + toks[i+1][0:4] + " " + toks[i+2] + " " + toks[i+3][0:4] + " " + toks[i+4] == "WHILE EXPR IS EXPR {" or toks[i] + " " + toks[i+1][0:4] + " " + toks[i+2] + " " + toks[i+3][0:3] + " " + toks[i+4] == "WHILE EXPR IS NUM {" or toks[i] + " " + toks[i+1][0:3] + " " + toks[i+2] + " " + toks[i+3][0:4] + " " + toks[i+4] == "WHILE NUM IS EXPR {":
                if toks[i+1][0:3] == "NUM" and toks[i+3][0:3] == "NUM":
                    if toks[i+1][4:] == toks[i+3][4:]:
                        i+=5
                        loopStarted = 1
                        while toks[i+1][4:] == toks[i+3][4:]:
                            break
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:6] == "STRING" and toks[i+3][0:6] == "STRING":
                    if toks[i+1][8:-1] == toks[i+3][8:-1]:
                        i+=5
                        loopStarted = 1
                        while toks[i+1][8:-1] == toks[i+3][8:-1]:
                            break
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "VAR" and toks[i+3][0:3] == "VAR":
                    if getVARIABLE(toks[i+1][7:]) == getVARIABLE(toks[i+3][7:]):
                        i+=5
                        loopStarted = 1
                        while getVARIABLE(toks[i+1][7:]) == getVARIABLE(toks[i+3][7:]):
                            break
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "BOOL" and toks[i+3][0:4] == "BOOL":
                    if toks[i+1][5:] == toks[i+3][5:]:
                        i+=5
                        loopStarted = 1
                        while toks[i+1][5:] == toks[i+3][5:]:
                            break
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:4] == "EXPR":
                    if eval(toks[i+1][5:]) == eval(toks[i+3][5:]):
                        i+=5
                        loopStarted = 1
                        while eval(toks[i+1][5:]) == eval(toks[i+3][5:]):
                            break
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:4] == "EXPR" and toks[i+3][0:3] == "NUM":
                    t = eval(toks[i+1][6:])
                    if str(t) == str(toks[i+3][5:]):
                        i+=5
                        loopStarted = 1
                        while str(t) == str(toks[i+3][5:]):
                            break
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
                elif toks[i+1][0:3] == "NUM" and toks[i+3][0:4] == "EXPR":
                    t = eval(toks[i+1][5:])
                    if str(t) == str(toks[i+1][5:]):
                        i+=5
                        loopStarted = 1
                        while str(t) == str(toks[i+1][5:]):
                            break
                    else:
                        prevState = 0
                        while(toks[i] != "}"):
                            if toks[i] == "}":
                                break
                            i+=1
            elif toks[i] == "ELSE" and prevState == 1:
                while(toks[i] != "}"):
                    if toks[i] == "}":
                        break
                    i+=1
                prevState = 0
            elif toks[i] == "ELSE" and prevState == 0:
                i+=1
            elif toks[i] == "BREAK":
                if loopStarted == 0:
                    print("ILLEGAL OPERATION: break outside a loop")
                    exit()
                elif loopStarted == 1:
                    break
            else:
                print("k")
                i+=1
        except IndexError:
            pass

def run():
    global currentFile
    currentFile = argv[1]
    data = open_file(argv[1])
    toks = lex(data)
    parse(toks)

run()
