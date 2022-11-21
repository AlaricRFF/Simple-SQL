# Simple(silly) SQL -- A Query Based Database
## Introduction
Simple SQL, called as "silly", is a naive query based interative database which is benchmarked after the SQL language. Silly is constructed using object oriented programming language C++ and support basic instructions such as `CREATE`, `INSERT`, `DELETE` and so on. This is a class project done during EECS 281 in university of Michigan - Ann Arbor. However, I'm still adding more features into the original framework.

## Functionalities
+ `CREATE`: create a new table with syntax as follows:
  ```SQL
  CREATE <tablename> <N> type1 type2 ... typeN column_name1 column_name2 ... column_nameN
  ```
    `N` should be a positive integer, `type` are limited to `int`, `string`, `double`, `bool`. The number of `type` and `column_name` should both align with `N`.
+ `QUIT`: Exit the database with all data removed with syntax as follows:
  ```SQL
  QUIT
  ```
+ `#`: Symbol for comment, everything behind it will be ignored.
+ `REMOVE`: remove an existing table from the database with syntax as follows:
  ```SQL
  REMOVE <tablename>
  ```
