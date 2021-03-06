grammar Unixql;

program : SELECT columns FROM table where? ';';

column : VARIABLE | VARIABLE ',';
columns : ALL | column_selection+=column+;
table : VARIABLE;
where : WHERE condition;
condition : VARIABLE '=' STRING;

SELECT : 'select';
FROM : 'from';
WHERE : 'where';
ALL : '*';
VARIABLE : [A-Za-z_][A-Za-z0-9_]*;
STRING : '\'' .*? '\'' ;
WS : [ \t] -> skip;