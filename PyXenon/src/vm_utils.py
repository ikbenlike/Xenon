import vm

def vm_check_stack_size(stack: vm.XenonStackVector) -> int:
    if stack.size - stack.cursor <= 10:
        stack.size += 100
        stack.vector += [XenonStackItem() for i in range(100)]
        return 0
    return 0

def vm_add_int_to_stack(stack: vm.XenonStackVector, value: int):
    vm_check_stack_size(stack)
    stack.vector[stack.cursor].type = vm.x_integer
    stack.vector[stack.cursor].data.anint = value
    stack.cursor += 1

def vm_generate_int(value: int) -> vm.XenonStackItem:
    item = vm.XenonStackItem()
    item.type = vm.x_integer
    item.data.anint = value
    return item

def vm_add_string_to_stack(stack: vm.XenonStackVector, value: str):
    vm_check_stack_size(stack)
    stack.vector[stack.cursor].type = vm.x_string
    stack.vector[stack.cursor].data.astring = value
    stack.cursor += 1

def vm_generate_string(value: str) -> vm.XenonStackItem:
    item = vm.XenonStackItem()
    item.type = vm.x_string
    item.data.astring = value
    return item

def vm_add_char_to_stack(stack: vm.XenonStackVector, value: str):
    vm_check_stack_size(stack)
    stack.vector[stack.cursor].type = vm.x_character
    stack.vector[stack.cursor].data.achar = value[0]
    stack.cursor += 1

def vm_generate_char(value: str) -> vm.XenonStackItem:
    item = vm.XenonStackItem()
    item.type = vm.x_character
    item.data.achar = value[0]
    return item

def vm_add_float_to_stack(stack: vm.XenonStackItem, value: float):
    vm_check_stack_size(stack)
    stack.vector[stack.cursor].type = vm.x_floating
    stack.vector[stack.cursor].data.afloat = value
    stack.cursor += 1

def vm_generate_float(value: float) -> vm.XenonStackItem:
    item = vm.XenonStackItem()
    item.type = vm.x_floating
    item.data.afloat = value
    return item

def vm_add_bool_to_stack(stack: vm.XenonStackVector, value: bool):
    vm_check_stack_size(stack)
    stack.vector[stack.cursor].type = vm.x_boolean
    stack.vector[stack.cursor].data.abool = value
    stack.cursor += 1

def vm_generate_bool(value: bool) -> vm.XenonStackItem:
    item = vm.XenonStackItem()
    item.type = vm.x_boolean
    item.data.abool = value
    return item

def vm_add_void_to_stack(stack: vm.XenonStackVector):
    vm_check_stack_size(stack)
    stack.vector[stack.cursor].type = vm.x_void
    stack.vector += 1

def vm_generate_void() -> vm.XenonStackItem:
    item = vm.XenonStackItem
    item.type = vm.x_void
    return item

def vm_add_opcode_to_stack(stack: vm.XenonStackVector, value: int):
    vm_check_stack_size(stack)
    stack.vector[stack.cursor].type = vm.x_opcode
    stack.vector[stack.cursor].data.anint = value
    stack.cursor += 1

def vm_generate_opcode(value: int) -> vm.XenonStackItem:
    item = vm.XenonStackItem()
    item.type = vm.x_opcode
    item.data.anint = value
    return item

def vm_add_func_to_stack(stack: vm.XenonStackVector, addr: int, nargs: int, nlocals: int, xret_t: int, xfunc_t: int):
    vm_check_stack_size(stack)
    stack.vector[stack.cursor].type = vm.x_function
    stack.vector[stack.cursor].data.func.addr = addr
    stack.vector[stack.cursor].data.func.nargs = nargs
    stack.vector[stack.cursor].data.func.nlocals = nlocals
    stack.vector[stack.cursor].data.func.xret_t = xret_t
    stack.vector[stack.cursor].data.func.xfunc_t = xfunc_t

def vm_generate_func(addr: int, nargs: int, nlocals: int, xret_t: int, xfunc_t: int) -> vm.XenonStackItem:
    item = XenonStackItem()
    item.type = vm.x_function
    item.data.func.addr = addr
    item.data.func.nargs = nargs
    item.data.func.nlocals = nlocals
    item.data.func.xret_t = xret_t
    item.data.func.xfunc_t = xfunc_t
    return item

def vm_get_type(stack: vm.XenonStackVector, i: int) -> int:
    return stack.vector[i].type
