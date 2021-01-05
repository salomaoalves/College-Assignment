class Lexico():
    def __init__(self, cadeia, head, col, line):
        self.head = head
        self.col = col
        self.fita = cadeia
        self.n_line = line
        self.tokens_table = ''
        self.symbols_table = {}
        self.lexema = ''
        self.end_line = '\n'
        self.caracter = ''
        
    def move_head_forward(self):
        self.col += 1
        self.head += 1

    def move_head_backward(self):
        self.col -= 1
        self.head -= 1

    def get_head_position(self):
        return self.head

    def update_number_line(self):
        self.col = 0
        self.n_line += 1

    def get_next_caracter(self):
        if self.head < len(self.fita):
            self.caracter = self.fita[self.head]
            self.move_head_forward()
            #if self.caracter != self.end_line orself.caracter != self.end_line or  not self.caracter.isspace():
            self.lexema += self.caracter
        return self.caracter


    def q0(self):
        if self.head < len(self.fita):
            self.caracter = self.get_next_caracter()
            if ':' == self.caracter:
                self.q1()
            elif '[' == self.caracter:
                self.q3()
            elif ')' == self.caracter:
                self.q5()
            elif '(' == self.caracter:
                self.q6()
            elif ',' == self.caracter:
                self.q7()
            elif '{' == self.caracter:
                self.q8()
            elif '}' == self.caracter:
                self.q9()
            elif ';' == self.caracter:
                self.q10()
            elif '/' == self.caracter:
                self.q11()
            elif '+' == self.caracter:
                self.q12()
            elif '-' == self.caracter:
                self.q13()
            elif '*' == self.caracter:
                self.q14()
            elif '>' == self.caracter:
                self.q16()
            elif '<' == self.caracter:
                self.q25()
            elif '"' == self.caracter:
                self.q21()
            elif self.caracter.isdigit():
                self.q22()
            elif '=' == self.caracter:
                self.q29()
            elif 'i' == self.caracter:
                self.q31()
            elif 'c' == self.caracter:
                self.q35()
            elif 'r' == self.caracter:
                self.q40()
            elif 's' == self.caracter:
                self.q45()
            elif 'e' == self.caracter:
                self.q52()
            elif 'f' == self.caracter:
                self.q68()
            elif 'p' == self.caracter:
                self.q73()
            elif self.caracter == self.end_line:
                self.update_number_line()
                self.lexema = self.end_line
                self.tokens_table = ["new_line", self.lexema, self.n_line, self.col-len(self.lexema), self.col, self.head]
            elif self.caracter.isspace():
                self.lexema = ''
                self.tokens_table = ["space", self.lexema, self.n_line, self.col-len(self.lexema), self.col, self.head]
            elif self.caracter not in ['c','r','i','s','p','e'] and self.caracter.isalpha():
                self.q65()
            else:
                raise Exception("Erro Léxico ({0}, {1}): Caracter {2} inesperado".format(self.n_line, self.col, self.caracter))
            return
        else:
            return


    def q1(self):
        self.caracter = self.get_next_caracter()
        if '=' == self.caracter:
            self.q2()
        else:
            raise Exception("Erro Léxico ({0}, {1}): Lexema {2} não reconhecido".format(self.n_line, self.col, self.lexema))

    def q3(self):
        self.caracter = self.get_next_caracter()
        if '*' == self.caracter:
            self.q4()
        else:
            raise Exception("Erro Léxico ({0}, {1}): Lexema {2} não reconhecido".format(self.n_line, self.col, self.lexema))

    def q12(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit():
            self.q22()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q66()

    def q13(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit():
            self.q22()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q67()

    def q14(self):
        self.caracter = self.get_next_caracter()
        if ']' == self.caracter:
            self.q18()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q17()

    def q16(self):
        self.caracter = self.get_next_caracter()
        if '=' == self.caracter:
            self.q20()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q19()

    def q21(self):
        self.caracter = self.get_next_caracter()
        if self.caracter not in ['\n','\v','\f','\r','"']:
            self.q21()
        elif '"' == self.caracter:
            self.q24()
        else:
            raise Exception("Erro Léxico ({0}, {1}): Caracter {2} inválido".format(self.n_line, self.col, self.caracter))

    def q25(self):
        self.caracter = self.get_next_caracter()
        if '>' == self.caracter:
            self.q27()
        elif '=' == self.caracter:
            self.q28()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q26()

    def q29(self):
        self.caracter = self.get_next_caracter()
        if '=' == self.caracter:
            self.q30()
        else:
            raise Exception("Erro Léxico ({0}, {1}): Caracter {2} inválido".format(self.n_line, self.col, self.caracter))

    def q31(self):
        self.caracter = self.get_next_caracter()
        if 'n' == self.caracter:
            self.q32()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'n' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q32(self):
        self.caracter = self.get_next_caracter()
        if 't' == self.caracter:
            self.q33()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 't' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q33(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit() and self.caracter.isalpha():
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q34()

    def q35(self):
        self.caracter = self.get_next_caracter()
        if 'h' == self.caracter:
            self.q36()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'h' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q36(self):
        self.caracter = self.get_next_caracter()
        if 'a' == self.caracter:
            self.q37()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'a' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q37(self):
        self.caracter = self.get_next_caracter()
        if 'r' == self.caracter:
            self.q38()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'r' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q38(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit() and self.caracter.isalpha():
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q39()

    def q40(self):
        self.caracter = self.get_next_caracter()
        if 'e' == self.caracter:
            self.q41()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'e' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q41(self):
        self.caracter = self.get_next_caracter()
        if 'a' == self.caracter:
            self.q42()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'a' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q42(self):
        self.caracter = self.get_next_caracter()
        if 'l' == self.caracter:
            self.q43()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'l' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q43(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit() and self.caracter.isalpha():
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q44()

    def q45(self):
        self.caracter = self.get_next_caracter()
        if 'e' == self.caracter:
            self.q46()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'e' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q46(self):
        self.caracter = self.get_next_caracter()
        if 'n' == self.caracter:
            self.q48()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'n' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q47()

    def q48(self):
        self.caracter = self.get_next_caracter()
        if 'a' == self.caracter:
            self.q49()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'a' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q49(self):
        self.caracter = self.get_next_caracter()
        if 'o' == self.caracter:
            self.q50()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'o' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q50(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit() and self.caracter.isalpha():
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q51()

    def q52(self):
        self.caracter = self.get_next_caracter()
        if 'n' == self.caracter:
            self.q53()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'n' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q53(self):
        self.caracter = self.get_next_caracter()
        if 'q' == self.caracter:
            self.q54()
        elif 't' == self.caracter:
            self.q61()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'q' != self.caracter and 't' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q54(self):
        self.caracter = self.get_next_caracter()
        if 'u' == self.caracter:
            self.q55()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'u' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q55(self):
        self.caracter = self.get_next_caracter()
        if 'a' == self.caracter:
            self.q56()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'a' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q56(self):
        self.caracter = self.get_next_caracter()
        if 'n' == self.caracter:
            self.q57()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'n' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q57(self):
        self.caracter = self.get_next_caracter()
        if 't' == self.caracter:
            self.q58()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 't' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q58(self):
        self.caracter = self.get_next_caracter()
        if 'o' == self.caracter:
            self.q59()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'o' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q59(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit() or self.caracter.isalpha():
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q60()

    def q61(self):
        self.caracter = self.get_next_caracter()
        if 'a' == self.caracter:
            self.q62()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'a' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q62(self):
        self.caracter = self.get_next_caracter()
        if 'o' == self.caracter:
            self.q63()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'o' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q63(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit() and self.caracter.isalpha():
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q64()

    def q68(self):
        self.caracter = self.get_next_caracter()
        if 'a' == self.caracter:
            self.q69()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'a' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q69(self):
        self.caracter = self.get_next_caracter()
        if 'c' == self.caracter:
            self.q70()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'c' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q70(self):
        self.caracter = self.get_next_caracter()
        if 'a' == self.caracter:
            self.q71()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'a' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q71(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit() and self.caracter.isalpha():
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q72()

    def q73(self):
        self.caracter = self.get_next_caracter()
        if 'r' == self.caracter:
            self.q74()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'r' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q74(self):
        self.caracter = self.get_next_caracter()
        if 'o' == self.caracter:
            self.q75()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'o' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q75(self):
        self.caracter = self.get_next_caracter()
        if 'g' == self.caracter:
            self.q76()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'g' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q76(self):
        self.caracter = self.get_next_caracter()
        if 'r' == self.caracter:
            self.q77()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'r' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q77(self):
        self.caracter = self.get_next_caracter()
        if 'a' == self.caracter:
            self.q78()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'a' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q78(self):
        self.caracter = self.get_next_caracter()
        if 'm' == self.caracter:
            self.q79()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'm' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q79(self):
        self.caracter = self.get_next_caracter()
        if 'a' == self.caracter:
            self.q80()
        elif self.caracter.isdigit() or (self.caracter.isalpha() and 'a' != self.caracter):
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q65()

    def q80(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit() and self.caracter.isalpha():
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.q81()


    # ---------------------------------- ESTADOS FINAIS ABAIXO -------------------------
    def q2(self):
        self.tokens_table = ["atribuicao", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q4(self):
        self.tokens_table = ["abre_comentario", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q5(self):
        self.tokens_table = ["fecha_parenteses", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q6(self):
        self.tokens_table = ["abre_parenteses", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q7(self):
        self.tokens_table = ["virgula", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q8(self):
        self.tokens_table = ["abre_bloco", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q9(self):
        self.tokens_table = ["fecha_bloco", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q10(self):
        self.tokens_table = ["final_linha", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q11(self):
        self.tokens_table = ["artop_/", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    #*
    def q17(self):
        self.tokens_table = ["artop_*", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    #*]
    def q18(self):
        self.tokens_table = ["fecha_comentario", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    #maior
    def q19(self):
        self.tokens_table = ["relop_>", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    #maior ou igual
    def q20(self):
        self.tokens_table = ["relop_>=", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    #numeros
    def q22(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit():
            self.q22()
        elif self.caracter == '.':
            self.q23()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.tokens_table = ["numero", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q23(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit():
            self.q23()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            self.tokens_table = ["numero", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    #STRING
    def q24(self):
        self.tokens_table = ["string", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    #<
    def q26(self):
        self.tokens_table = ["relop_<", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    #<>
    def q27(self):
        self.tokens_table = ["relop_<>", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    #<=
    def q28(self):
        self.tokens_table = ["relop_<=", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    #==
    def q30(self):
        self.tokens_table = ["relop_==", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q34(self):
        self.tokens_table = ["tipo_int", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q39(self):
        self.tokens_table = ["tipo_char", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q44(self):
        self.tokens_table = ["tipo_real", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q47(self):
        self.tokens_table = [self.lexema, self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q51(self):
        self.tokens_table = [self.lexema, self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q60(self):
        self.tokens_table = [self.lexema, self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q64(self):
        self.tokens_table = [self.lexema, self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q65(self):
        self.caracter = self.get_next_caracter()
        if self.caracter.isdigit() or self.caracter.isalpha():
            self.q65()
        else:
            self.move_head_backward()
            self.lexema = self.lexema[:-1]
            if self.lexema not in self.symbols_table.keys():
                self.symbols_table[self.lexema] = 1
            else:
                self.symbols_table[self.lexema] += 1
            
            self.tokens_table = ["id", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q66(self):
        self.tokens_table = ["artop_+", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q67(self):
        self.tokens_table = ["artop_-", self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q72(self):
        self.tokens_table = [self.lexema, self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]

    def q81(self):
        self.tokens_table = [self.lexema, self.lexema, self.n_line, self.col-len(self.lexema), self.col+1, self.head]



def lex(W, head, col, line):
    if len(W) == head:
        return False

    lexico = Lexico(W, head, col, line)
    lexico.q0()

    return lexico.tokens_table