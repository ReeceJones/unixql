# UnixQL
A shell environment for Unix-like systems that operates like a SQL database.

## Example Syntax
### List files
```
select name from ls;
```
### List files owned by specific user
```
select * from ls where user='root';
```

## How does it work
UnixQL uses a set of built in parsers to transform command output into a table representation.