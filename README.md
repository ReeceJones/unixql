# UnixQL
A shell environment for Unix-like systems that operates like a SQL database;

## Commonly asked questions
**Why?**

Parsing command output can sometimes be frustrating on normal shells. In response to this,
a madman might think it be reasonable to use SELECT statements to run commands. 

**But this is more effort than before**

That's not a question, stop taking the fun out of it

**This is stupid**

Thank you

## Example Syntax
### List files
```
SELECT name FROM ls;
```
### Execute command with parameters
```
SELECT * FROM (git status) WHERE status='changed';
```
### Redirect input
```
(SELECT * FROM echo) FROM <(file);
```
### Redirect output
```
CREATE FILE ls_output AS (SELECT * FROM ls);
```
### Custom parsing
```
SELECT DISTINCT [2] FROM %(ls -lA)
WITH PARSEROPTIONS (
    DELIM='\w+',
    SKIPROWS=1
);
```
### Column concatenation
```
SELECT *, %(SELECT * FROM (cat ls.name)) FROM ls;
```
### Join command outputs
```
SELECT a.name FROM (ls foo) AS a
INNER JOIN (ls bar) as b ON a.name=b.name;
```

## Query types

| Query type      | Use                 | Syntax    |
|-----------------|---------------------|-----------|
| Subquery        | Subquery            | `(...)`   |
| File input      | File input          | `<(...)`  |
| Raw command     | Execute raw command | `%(...)`  |


## How does it work
UnixQL uses a set of built in parsers to transform command output into a table representation.