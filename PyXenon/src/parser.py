class Parser:
    
    class Token:
        def __init__(self, start: int, end: int):
            self.start = start
            self.end = end

    class AbstractSyntaxTree:
        class Leaf:
            def __init__(self, parent, children, token: str):
                self.parent = parent
                self.children = children
                self.token = token
        def __init__(self):
            self.trunk = None

    def __init__(self, text: str):
        self.text = text
        self.tlen = len(self.text)
        self.instring = False
        self.index = 0
        self.tindex = 0
        self.white = "\t\n "
        self.delim = "[]\{\},.@-+!#$%*=()&|;"
        self.tokens = []
        self.keys = ["auto", "extrn", "int", "float", "char", "fn"]

    def parse(self) -> [Token]:
        t = None
        i = 0
        while self.index < self.tlen:
            #print(self.text[self.index])
            if self.text[self.index] == "\"":
                t = self.Token(self.index, 0)
                self.index += 1
                while self.text[self.index] != "\"":
                    self.index += 1
                    if self.index >= self.tlen:
                        break

                t.end = self.index + 1
                self.index += 1
                self.tokens += [t]
                self.tindex += 1
            elif self.text[self.index] == "\'":
                t = self.Token(self.index, 0)
                self.index += 1
                while self.text[self.index] != "\'":
                    self.index += 1
                    if self.index >= self.tlen:
                        break

                t.end = self.index + 1
                self.index += 1
                self.tokens += [t]
                self.tindex += 1
            else:
                t = self.Token(self.index, 0)
                #print(self.text[self.index])
                while self.text[self.index] not in self.white and self.text[self.index] not in self.delim:
                    self.index += 1
                    if self.index >= self.tlen:
                        break

                t.end = self.index
                if t.end == t.start:
                    if self.text[self.index] not in self.white:
                        self.index += 1
                        t.end = self.index
                        self.tokens += [t]
                    self.index += 1
                    continue
                if self.text[self.index] in self.white:
                    self.index += 1
                self.tokens += [t]
                self.tindex += 1
                if self.index < self.tlen:
                    if self.text[self.index] in self.delim:
                        t = self.Token(self.index, 0)
                        t.end = self.index + 1
                        self.tokens += [t]
                        self.index += 1
                        self.tindex += 1
                    elif self.text[self.index - 1] in self.delim:
                        t = self.Token(self.index - 1, 0)
                        t.end = self.index 
                        self.tokens += [t]
                        self.index += 1
                        self.tindex += 1

    def construct_ast(self) -> AbstractSyntaxTree:
        self.ast = self.AbstractSyntaxTree()
        self.ast.trunk = self.AbstractSyntaxTree.Leaf(None, None, "Ast")
        prev_tok = self.ast.trunk
        for x in self.tokens:
            if self.text[x.start:x.end] == "+":
                pass
            elif self.text[x.start:x.end] == "-":
                pass
            elif self.text[x.start:x.end] == "fn":
                pass
