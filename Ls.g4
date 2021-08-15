grammar Ls;

output : ANYCOL EOF;
// line : file_mode number_links user group size month day time path CRLF?;

// file_mode : ANYCOL;
// number_links : ANYCOL;
// user : ANYCOL;
// group : ANYCOL;
// size : ANYCOL;
// day : ANYCOL;
// month : ANYCOL;
// time : ANYCOL;
// path : ANYCOL;

ANYCOL : [A-Za-z0-9]+;
CRLF : '\n';
WS : ' ' -> skip;