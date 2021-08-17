grammar Output;

ls : (ANYCOL ANYCOL CRLF) entries+=line+ EOF;
line : file_mode number_links user group size month day time path+=ANYCOL CRLF;

file_mode : ANYCOL;
number_links : ANYCOL;
user : ANYCOL;
group : ANYCOL;
size : ANYCOL;
day : ANYCOL;
month : ANYCOL;
time : ANYCOL;

ANYCOL : '"' .*? [^\\]["] | [A-Za-z0-9\-:._()]+;
CRLF : '\r'? '\n';
WS : ' ' -> skip;