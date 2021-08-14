grammar Unixql;

program : SELECT columns FROM table ';';

column : VARIABLE | VARIABLE ',';
columns : column_selection+=column+;
table : VARIABLE;

SELECT : 'select';
FROM : 'from';
VARIABLE : [A-Za-z_][A-Za-z0-9_]*;
WS : [ \t] -> skip;