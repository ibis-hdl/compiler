#! /usr/bin/env python3
# coding: utf-8

'''
Copy&Paste 
http://rti.etf.bg.ac.rs/rti/ri5rvl/tutorial/TUTORIAL/IEEE/HTML/1076_13.HTM#13.1

FixMe: Find better Codepage Web Reference
'''

import re

# ISO 8859:1 Charsets 8-bit
UppercaseLetters = r"A B C D E F G H I J K L M N O P Q R S T U V W X Y Z А Б В Ã Д Е Ж З И Й К Л М Н О П С Т У Ô Õ Ц Ø Щ Ъ Ы Ь Ý Þ"
Digits = r"0 1 2 3 4 5 6 7 8 9"
SpecialCharacters = r" # & ' () * + , - . / : ; < = > [ ] _ |"
LowercaseLetters = r"a b c d e f g h i j k l m n o p q r s t u v w x y z Я а б в г д е ж з и й к л м н о п ð с т у ф х ц ø щ ъ ы ь ý þ я"
OtherSpecialCharacters = r"! $ % @ ? \ ^ ` { } ~ ¡ ¢ £ ¤ ¥ ¦ § ¨ © ª « ~ ® ¯ ° ± ² ³ ' µ ¶ · ¸ ¹ º » 1/4 1/2 3/4 ¿ × ÷ -"

def cxx_char_list(alist, as_cp=False):
    '''
    Create C++11 raw char list
    '''
    if as_cp:
        return map(lambda x: '"' + str(ord(x)) + '"', alist.split())
    else:
        return map(lambda x: 'u"' + x + '"', alist.split())

def my_list_printer(name, alist):
    tmp = cxx_char_list(alist)
    print(name + ' = {' + ", ".join(tmp) + '};')

def cxx_parser_class(alist):
    '''
    Create the character class string for the parser
    '''
    return 'u"' + "".join(alist.split()) + '"'

def my_char_class_printer(name, alist):
    tmp = cxx_parser_class(alist)
    print(name + '_cls = ' + tmp)


my_list_printer('UppercaseLetters', UppercaseLetters)
my_list_printer('Digits', Digits)
my_list_printer('SpecialCharacters', SpecialCharacters)
my_list_printer('LowercaseLetters', LowercaseLetters)
my_list_printer('OtherSpecialCharacters', OtherSpecialCharacters)

my_char_class_printer('UppercaseLetters', UppercaseLetters)
my_char_class_printer('Digits', Digits)
my_char_class_printer('SpecialCharacters', SpecialCharacters)
my_char_class_printer('LowercaseLetters', LowercaseLetters)
my_char_class_printer('OtherSpecialCharacters', OtherSpecialCharacters)

