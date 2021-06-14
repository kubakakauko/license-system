# knack-query-builder

A simple and very lightweight sql query builder. Written for my
personal usage in various projects. It was designed for the usage
in combination with mysql.

```JS
const knack = require('knack-sql')

const connection = knack.mysql.createConnection({
  host: ''
  user: ''
  password: ''
  database: ''
  port: 3306
})
```

And the usage afterwards is quite simple as that:

```JS
connection.connect(err => {
  if (err) {
    console.log(err)
  } else {
    connection.query(
      knack.create('table_name')
      .integer('id')
        .auto_increment()
      .string('name')
        .not_null()
        .default('')
      .serialize()
    )
  }
})
```

## Supports

- `SELECT`
- `INSERT INTO`
- `UPDATE`
- `DELETE FROM`
- `CREATE TABLE`
- `CREATE TABLE IF NOT EXISTS`
