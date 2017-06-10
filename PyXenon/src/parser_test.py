import parser

with open("test.xenon", "r") as f:
    p = parser.Parser(f.read())
    p.parse()
    for x in p.tokens:
        print(p.text[x.start:x.end])
