grammar Ls;

output : (ANYCOL ANYCOL CRLF) entries+=line+ EOF;
line : file_mode number_links user group size month time path? CRLF;

file_mode : ANYCOL;
number_links : ANYCOL;
user : ANYCOL;
group : ANYCOL;
size : ANYCOL;
month : ANYCOL;
time : ANYCOL;
path : PATHCOL;

ANYCOL : [A-Za-z0-9\-:];
PATHCOL : .+;
CRLF : '\r'? '\n';
WS : [ \t] -> skip;