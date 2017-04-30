eda.VHDL93 {#mainpage}
==========

VHDL93 Parser at this time


Resources
---------

The "Gold" IEEE Standard VHDL Language Reference Manual (LRM):

- [IEEE 1076-1987](http://dx.doi.org/10.1109/IEEESTD.1988.122645)
- [IEEE 1076-1993](http://dx.doi.org/10.1109/IEEESTD.1994.121433)
- [IEEE 1076-2000](http://dx.doi.org/10.1109/IEEESTD.2000.92297)
- [IEEE 1076-2002](http://dx.doi.org/10.1109/IEEESTD.2002.93614)
- [IEEE 1076-2008](http://dx.doi.org/10.1109/IEEESTD.2009.4772740)

At least one LRM is online for VHDL93 (IEEE Std. 1076-1993)

- http://rti.etf.bg.ac.rs/rti/ri5rvl/tutorial/TUTORIAL/IEEE/HTML/1076_TOC.HTM

and a BNF for the
[IEEE Std 1076-2002](https://guest.iis.ee.ethz.ch/~zimmi/download/vhdl02_syntax.html)
standard at the ETH Zürich.


The VHDL93 Boost.Spirit X3 grammar refers to the former
[grammar]( http://rti.etf.bg.ac.rs/rti/ri5rvl/tutorial/TUTORIAL/IEEE/HTML/1076_AXA.HTM)
URL. Each production rule has a hyperlink to the appropriate LRM text.
For quick elaborating the BNF rules the
[hyperlinked grammar](https://tams.informatik.uni-hamburg.de/vhdl/tools/grammar/vhdl93-bnf.html)
is also useful.


There are also public online resources, especially for VHDL's BNF only:
- http://www.amos.eguru-il.com/vhdl_info/vhdl87_syntax.html
- http://www.amos.eguru-il.com/vhdl_info/vhdl93_syntax.html

This is not the first attempt to write an VHDL parser.
[Parsing VHDL is [very] hard](http://eli.thegreenplace.net/2009/05/19/parsing-vhdl-is-very-hard)
gives some points. Practical experience and hence useful is shown in the paper
[A Note on the Parsing of Complete VHDL-2002](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.143.917)
and in the cited article
[A VHDL compiler based on attribute grammar methodology](https://dl.acm.org/citation.cfm?id=74829)
which it refers. Sometimes there arises some funny problems like
- [Question about type_mark bnf](https://groups.google.com/forum/#!topic/comp.lang.vhdl/exUhoMrFavU)
  from comp.lang.vhdl
- unfortunately, the other I din't find any more - from standard committee talk?
