import regex

class AsmFunction:
    def __init__(self, address, bytes):
        self.address = address
        self.bytes = bytes
        self.gadgets = {}

mov_dict = {
0xc0:'%{0}ax,%{0}ax', 0xc1:'%{0}ax,%{0}cx', 0xc2:'%{0}ax,%{0}dx', 0xc3:'%{0}ax,%{0}bx', 0xc4:'%{0}ax,%{0}sp', 0xc5:'%{0}ax,%{0}bp', 0xc6:'%{0}ax,%{0}si', 0xc7:'%{0}ax,%{0}di',
0xc8:'%{0}cx,%{0}ax', 0xc9:'%{0}cx,%{0}cx', 0xca:'%{0}cx,%{0}dx', 0xcb:'%{0}cx,%{0}bx', 0xcc:'%{0}cx,%{0}sp', 0xcd:'%{0}cx,%{0}bp', 0xce:'%{0}cx,%{0}si', 0xcf:'%{0}cx,%{0}di',
0xd0:'%{0}dx,%{0}ax', 0xd1:'%{0}dx,%{0}cx', 0xd2:'%{0}dx,%{0}dx', 0xd3:'%{0}dx,%{0}bx', 0xd4:'%{0}dx,%{0}sp', 0xd5:'%{0}dx,%{0}bp', 0xd6:'%{0}dx,%{0}si', 0xd7:'%{0}dx,%{0}di',
0xd8:'%{0}bx,%{0}ax', 0xd9:'%{0}bx,%{0}cx', 0xda:'%{0}bx,%{0}dx', 0xdb:'%{0}bx,%{0}bx', 0xdc:'%{0}bx,%{0}sp', 0xdd:'%{0}bx,%{0}bp', 0xde:'%{0}bx,%{0}si', 0xdf:'%{0}bx,%{0}di',
0xe0:'%{0}sp,%{0}ax', 0xe1:'%{0}sp,%{0}cx', 0xe2:'%{0}sp,%{0}dx', 0xe3:'%{0}sp,%{0}bx', 0xe4:'%{0}sp,%{0}sp', 0xe5:'%{0}sp,%{0}bp', 0xe6:'%{0}sp,%{0}si', 0xe7:'%{0}sp,%{0}di',
0xe8:'%{0}bp,%{0}ax', 0xe9:'%{0}bp,%{0}cx', 0xea:'%{0}bp,%{0}dx', 0xeb:'%{0}bp,%{0}bx', 0xec:'%{0}bp,%{0}sp', 0xed:'%{0}bp,%{0}bp', 0xee:'%{0}bp,%{0}si', 0xef:'%{0}bp,%{0}di',
0xf0:'%{0}si,%{0}ax', 0xf1:'%{0}si,%{0}cx', 0xf2:'%{0}si,%{0}dx', 0xf3:'%{0}si,%{0}bx', 0xf4:'%{0}si,%{0}sp', 0xf5:'%{0}si,%{0}bp', 0xf6:'%{0}si,%{0}si', 0xf7:'%{0}si,%{0}di',
0xf8:'%{0}di,%{0}ax', 0xf9:'%{0}di,%{0}cx', 0xfa:'%{0}di,%{0}dx', 0xfb:'%{0}di,%{0}bx', 0xfc:'%{0}di,%{0}sp', 0xfd:'%{0}di,%{0}bp', 0xfe:'%{0}di,%{0}si', 0xff:'%{0}di,%{0}di'
}

popq_dict = {0x58:'%rax', 0x59:'%rcx', 0x5a:'%rdx', 0x5b:'%rbx', 0x5c:'%rsp', 0x5d:'%rbp', 0x5e:'%rsi', 0x5f:'%rdi'}

func_nop_dict = {0xc0:'%al,%al,', 0xc9:'%cl,%cl', 0xd2:'%dl,%dl', 0xdb:'%bl,%bl'}

def is_movq(AsmFunction, offset):
    bytes = AsmFunction.bytes
    if offset < len(bytes) - 2 and bytes[offset] == 0x48 and bytes[offset+1] == 0x89 and bytes[offset+2] in mov_dict:
        instruction = "movq " + mov_dict[bytes[offset+2]].format('r')
        return instruction, 3

    return None, None

def is_movl(AsmFunction, offset):
    bytes = AsmFunction.bytes
    if offset < len(bytes) - 1 and bytes[offset] == 0x89 and bytes[offset + 1] in mov_dict:
        instruction = "movl " + mov_dict[bytes[offset + 1]].format('e')
        return instruction, 2

    return None, None

def is_popq(AsmFunction, offset):
    bytes = AsmFunction.bytes
    if offset < len(bytes) and bytes[offset] in popq_dict:
        instruction = "popq " + popq_dict[bytes[offset]]
        return instruction, 1

    return None, None

def is_ret(AsmFunction, offset):
     bytes = AsmFunction.bytes
     if offset < len(bytes) and bytes[offset] == 0xc3:
         return "ret", 1

     return None, None

def is_nop(AsmFunction, offset):
    bytes = AsmFunction.bytes
    if offset > len(bytes) - 1:
        return None, None
    if bytes[offset] == 0x90:
        instruction = "nop"
        return instruction, 1
    return None, None

def is_fuctional_nop(AsmFunction, offset):
    bytes = AsmFunction.bytes
    if offset > len(bytes) - 2:
        return None, None
    instruction = None
    if bytes[offset] == 0x20 and bytes[offset + 1] in func_nop_dict:
        instruction = "andb " + func_nop_dict[bytes[offset + 1]]
    elif bytes[offset] == 0x08 and bytes[offset + 1] in func_nop_dict:
        instruction = "orb " + func_nop_dict[bytes[offset + 1]]
    elif bytes[offset] == 0x38 and bytes[offset + 1] in func_nop_dict:
        instruction = "cmpb " + func_nop_dict[bytes[offset + 1]]
    elif bytes[offset] == 0x84 and bytes[offset + 1] in func_nop_dict:
        instruction = "testb " + func_nop_dict[bytes[offset + 1]]
    if instruction:
        return instruction, 2

    return None, None

def parse_file(filename):
    lines = []
    with open(filename, 'r') as f:
        lines = f.readlines()

    asmfunctions = []
    address_re = regex.compile('^[0-9a-f]{16}')
    bytes_re = regex.compile('^([0-9a-f]{2})(?: ([0-9a-f]{2}))*\s$')

    # iterate two values at a time
    it = iter(lines)
    for current_line in it:
        # Check if current line is an address
        address_match = address_re.match(current_line)
        if not address_match:
            continue
        # Check if next line is an opcode line
        try:
            next_line = next(it)
            bytes_match = bytes_re.match(next_line)
            if not bytes_match:
                raise ValueError('bad bytes line')
        except StopIteration:
            break

        base_address = int(address_match.group(0), 16)
        bytes = [int(i, 16) for i in bytes_match.captures(1) + bytes_match.captures(2)]
        asmfunction = AsmFunction(base_address, bytes)
        asmfunctions.append(asmfunction)

    return asmfunctions

def add_or_append_current_instr(asmfunction, instruction, offset):
    if hasattr(asmfunction, "current_test_gadget"):
        asmfunction.current_test_gadget.append(instruction)
    else:
        asmfunction.current_test_gadget = [instruction]
        asmfunction.initial_offset = offset

def finish_instr_set(asmfunction):
    if hasattr(asmfunction, "current_test_gadget"):
        asmfunction.gadgets[asmfunction.address + asmfunction.initial_offset] = asmfunction.current_test_gadget
        del asmfunction.current_test_gadget
        del asmfunction.initial_offset

def check_for_gadget(asmfunction, offset = 0):
    # stop condition
    if offset >= len(asmfunction.bytes):
        finish_instr_set(asmfunction)
        return

    # try all possibilities
    instruction, length = is_movq(asmfunction, offset)
    if not instruction:
        instruction, length = is_popq(asmfunction, offset)
    if not instruction:
        instruction, length = is_movl(asmfunction, offset)
    if not instruction:
        instruction, length = is_fuctional_nop(asmfunction, offset)
    if not instruction:
        instruction, length = is_nop(asmfunction, offset)
    if not instruction:
        instruction, length = is_ret(asmfunction, offset)

    if instruction and length:
        add_or_append_current_instr(asmfunction, instruction, offset)
        if instruction == "ret":
            finish_instr_set(asmfunction)
        check_for_gadget(asmfunction, offset + length)

    if not hasattr(asmfunction, "current_test_gadget"):
        check_for_gadget(asmfunction, offset + 1)
    else:
        del asmfunction.current_test_gadget
        del asmfunction.initial_offset

if __name__ == '__main__':
    asmfunctions = parse_file('ops.txt')

    for index,asmfunction in enumerate(asmfunctions):
            check_for_gadget(asmfunction)
            for key, value in asmfunction.gadgets.items():
                print(format(key, 'x'), " :", value)

