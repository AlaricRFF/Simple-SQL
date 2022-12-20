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
+ `INSERT`: insert rows into a specified table with syntax as follows:
  ```SQL
    INSERT INTO <tablename> <N> ROWS
    <value12> ... <value1M>
    <value22> ... <value2M>
    ...
    <valueN2> ... <valueNM>
  ```
where the data type should match with predefined data type in the table to be inserted.
+ `PRINT`: print specified data from an existing table with syntax as follows:
  ```SQL
    PRINT FROM <tablename> <N> <print_colname1> <print_colname2> ... <print_colameN> ALL
  ```
  which prints the whole table
  or:
  ```SQL
    PRINT FROM <tablename> <N> <print_colname1> <print_colname2> ... <print_colnameN> WHERE <column_name> <OP> <value>
  ```
  where `OP` is limited to `<`, `>` and `=`.
+ `DELETE` : delete certain rows from a table with syntax as follows:
  ```SQL
    DELETE FROM <tablename> WHERE <column_name> <OP> <value>
  ```
  where `OP` is limited to `<`, `>` and `=`.
+ `JOIN`: Join two tables where values in selected columns match, and print results. Te syntax is as follows:
  ```SQL
    JOIN <tablename1> AND <tablename2> WHERE <colname1> = <colname2> AND PRINT <N> <print_colname1> <1|2> <print_colname2> <1|2> ... <print_colnameN> <1|2>
  ```
  Directs the program to print the data in `N` columns, selected by `print_colname1`, `print_colname2`, … `print_colnameN`. The `print_colname`s will be the names of columns in either the first table `tablename1` or the second table `tablename2`, as chosen by the `<1/2>` argument directly following each `print_colname`. `OP` in `JOIN` will be limited to `=`.
+ `GENERATE`: create a hash table or BST map on a given column with each row's data in that as content. The syntax is as follows:
  ```SQL
    GENERATE FOR <tablename> <indextype> INDEX ON <colname>
  ```
  The `GENERATE` command will accelerate the speed of following command which may use a column data very often.
+ `UPDATE`: delete a column or add a new column in the specified table, the syntax shown as follows:
   ```SQL
    UPDATE <tablename> ON <column_name> TYPE {DELETE | ADD} {NULL (if DELETE) | <type> (if ADD)}
   ```

## Usage
+ `make all`: Compile the whole program
+ `make clean`: Delete all object files inside the `/obj` directory as well as the binary
+ `make run`: compile the whole program to the newest state and run `silly` the SQL.

## Still Working On...
+ `UPDATE`: delete a column or add new column for a given table.
+ `TRIGGER`: create a table linked with a parent table which updates itself after some user defined action of the parent table.
+ `SELECT`: select certain row indexes in a given table with a given criteria, which supports nested `SELECT` and enable the indexes selected to be passed over to other operations.
