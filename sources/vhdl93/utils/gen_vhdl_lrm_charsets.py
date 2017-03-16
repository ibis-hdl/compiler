#! /usr/bin/env python3
# coding: utf-8

"""
ISO-8859-1 was incorporated as the first 256 code points of ISO/IEC 10646 and Unicode. 

Python 3.x doesn't have a special Unicode string type/class. Every string is a 
Unicode string. So the developers finally removed the unichr function in favor 
of a common chr which now does what the old unichr did.

code table:
ftp://ftp.unicode.org/Public/MAPPINGS/ISO8859/8859-1.TXT
http://www.gymel.com/charsets/ISO8859-1.html
"""


import unicodedata

class Vhdl93CharSet:
    '''
    Each graphic character corresponds to a unique code of the ISO eight-bit 
    coded character set (ISO 8859-1)
    '''
        
    def isupper(self, cp):
        uc_dict = {
            'Lu' : True
        }
        category = unicodedata.category(chr(cp))
        return uc_dict.get(category, False)
    
    def islower(self, cp):
        uc_dict = {
            'Ll' : True
        }
        uc_blacklist = [
            'µ'
        ]
        category = unicodedata.category(chr(cp))
        if chr(cp) in uc_blacklist:
            return False
        return uc_dict.get(category, False)
    
    def isdigit(self, cp):
        uc_dict = {
            'Nd' : True , 
            'No' : False
        }
        category = unicodedata.category(chr(cp))
        return uc_dict.get(category, False)

    def isSpecialCharacter(self, cp):
        SpecialCharacters = r'''" # & ' ( ) * + , - . / : ; < = > [ ] _ |'''
        if chr(cp) in SpecialCharacters.split(): 
            return True
        return False
    
    def isOtherSpecialCharacter(self, cp):
        # LRM 2k pg. 175/30
        uc_dict = {
            'Pc' : True, # Punctuation, Connector
            'Pd' : True, # Punctuation, Dash
            'Ps' : True, # Punctuation, Open
            'Pe' : True, # Punctuation, Close
            'Pi' : True, # Punctuation, Initial quote
            'Pf' : True, # Punctuation, Final quote
            'Po' : True, # Punctuation, Other
            'No' : True, # Number, Other
            'Sm' : True, # Symbol, Math
            'Sc' : True, # Symbol, Currency
            'Sk' : True, # Symbol, Modifier
            'So' : True, # Symbol, Other
            'Cf' : True, # Other, Format
        }
        uc_whitelist = [
            'µ', # Ll
            'ª', # Lo (Feminine ordinal indicator)
            'º', # Lo (Masculine ordinal indicator)
        ]
        category = unicodedata.category(chr(cp))
        if self.isSpecialCharacter(cp):
            return False
        if chr(cp) in uc_whitelist:
            return True
        return uc_dict.get(category, False)
    
    def isFormatEffector(self, cp):
        # https://en.wikipedia.org/wiki/Escape_sequences_in_C
        FormatEffector = r"\t \n \v \f \r"
        if chr(cp) in FormatEffector.split(): 
            return True
        return False
    
    def getCategory(self, c):
        return unicodedata.category(c)
    
    def classify(self, class_callback):
        alist = []
        for codepoint in range(0, 256):
            if class_callback(codepoint):
                alist.append(chr(codepoint))
        return alist
    
    def UppercaseLetters(self):
        return "".join(self.classify(self.isupper))
    
    def LowercaseLetters(self):
        return "".join(self.classify(self.islower))
    
    def Digits(self):
        return "".join(self.classify(self.isdigit))
    
    def SpecialCharacter(self):
        return "".join(
            list(map(self.escapeCxx, self.classify(self.isSpecialCharacter)))
        )
    
    def OtherSpecialCharacter(self):
        '''
        for cp in self.classify(self.isOtherSpecialCharacter):
            print(cp + ' ' + '\\x{:x}'.format(ord(cp)) + ' ' + unicodedata.name(cp, "N/A"))
        '''
        return "".join(
            list(map(self.escapeCxx, self.classify(self.isOtherSpecialCharacter)))
            )
    
    def escapeCxx(self, ch):
        esc_dict = { r'\\' : r'\\\\' , r'"' : r'\"'}
        #print(ch + ' -> ' + esc_dict.get(ch, ch))
        return esc_dict.get(ch, ch)
    

if __name__ == "__main__":
    gen = Vhdl93CharSet()
    print('UppercaseLetters = \"' + gen.UppercaseLetters() + '\"')
    print('LowercaseLetters = \"' + gen.LowercaseLetters() + '\"')
    print('Digits = \"' + gen.Digits() + '\"')
    print('SpecialCharacters = \"' + gen.SpecialCharacter() + '\"')
    print('OtherSpecialCharacters = \"' + gen.OtherSpecialCharacter() + '\"')
    
    
    '''
    print(gen.getCategory("µ"))
    print(gen.getCategory("¨"))
    print(gen.getCategory("ª"))
    print(gen.getCategory("º"))
    print(gen.getCategory("¯"))
    print(unicodedata.category(chr(0xAD))) # soft-hyphen
    print(hex(ord('·')))
    ''' 
