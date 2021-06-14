"use strict"

const mysql = require('mysql')

const knack_where_ops = {
  lessThan:           1,
  greaterThan:        2,
  lessThanOrEqual:    3,
  greaterThanOrEqual: 4
}

class knack_basic_query
{
  constructor(query)
  {
    this.data = typeof(query) === 'string' ? query : ''
  }

  serialize()
  {
    return this.data + ';'
  }
}

class knack_table extends knack_basic_query
{
  constructor(query)
  {
    super(query)
    this.increment = null
    this.last      = null
    this.final     = ''
  }

  insert_trim()
  {
    if (this.last !== null) {
      this.data += ', '
    }
    return this
  }

  serialize()
  {
    let str = this.data
    if (typeof(this.increment) === 'string') {
      str += `, PRIMARY KEY(${mysql.escapeId(this.increment)})`
    }
    return str + `)${this.final};`
  }

  not_null()
  {
    this.data += ' NOT NULL'
    return this
  }

  default(value)
  {
    this.data += ` DEFAULT ${mysql.escape(value)}`
    return this
  }

  auto_increment()
  {
    this.increment =  this.last
    this.data      += ' AUTO_INCREMENT'
    return this
  }

  integer(name, size = 4)
  {
    this.insert_trim()
    this.data += `${mysql.escapeId(name)} int(${size})`
    this.last = name
    return this
  }

  string(name, length = 256)
  {
    this.insert_trim()
    this.data += `${mysql.escapeId(name)} varchar(${length})`
    this.last = name
    return this
  }

  text(name)
  {
    this.insert_trim()
    this.data += `${mysql.escapeId(name)} text`
    this.last = name
    return this
  }
}

class knack_query extends knack_basic_query
{
  from(table)
  {
    this.data += ` FROM ${mysql.escapeId(table)}`
    return this
  }

  where(...pairs)
  {
    if (pairs.length > 0) {
      let first = false
      pairs.forEach(pair => {
        const get_operator = () => {
          if (pair.length === 3) {
            switch (pair[2]) {
            case knack_where_ops.lessThan:
              return '<'
            case knack_where_ops.greaterThan:
              return '>'
            case knack_where_ops.lessThanOrEqual:
              return '<='
            case knack_where_ops.greaterThanOrEqual:
              return '>='
            default:
              break
            }
          }
          return '='
        }
        if (!first) {
          this.data += ` WHERE ${mysql.escapeId(pair[0])} ${get_operator()} ${mysql.escape(pair[1])}`
          first = true
        } else {
          this.data += ` AND ${mysql.escapeId(pair[0])} ${get_operator()} ${mysql.escape(pair[1])}`
        }
      })
    }
    return this
  }

  set(...pairs)
  {
    if (pairs.length > 0) {
      let first = false
      pairs.forEach(pair => {
        if (!first) {
          this.data += ` SET ${mysql.escapeId(pair[0])} = ${mysql.escape(pair[1])}`
          first = true
        } else {
          this.data += `, ${mysql.escapeId(pair[0])} = ${mysql.escape(pair[1])}`
        }
      })
    }
    return this
  }

  values(...pairs)
  {
    if (pairs.length > 0) {
      let first = false
      let params = '', args = ''
      pairs.forEach(pair => {
        if (!first) {
          first = true
          params += `(${mysql.escapeId(pair[0])}`
          args   += `(${mysql.escape(pair[1])}`
        } else {
          params += `, ${mysql.escapeId(pair[0])}`
          args   += `, ${mysql.escape(pair[1])}`
        }
      })
      this.data += ` ${params}) VALUES ${args})`
    }
    return this
  }

  limit(count)
  {
    if (typeof(count) === 'number' && count > 0) {
      this.data += ` LIMIT ${count}`
    }
    return this
  }
}

const mysql_select = (...args) => {
  let query = 'SELECT '
  if (args.length > 0) {
    let first = false
    args.forEach(arg => {
      if (!first) {
        query += `${mysql.escapeId(arg)}`
        first = true
      } else {
        query += `, ${mysql.escapeId(arg)}`
      }
    })
  }
  else {
    query += '*'
  }
  return new knack_query(query)
}

const mysql_update = (table) => {
  return new knack_query(`UPDATE ${mysql.escapeId(table)}`)
}

const mysql_insert_into = (table) => {
  return new knack_query(`INSERT INTO ${mysql.escapeId(table)}`)
}

const mysql_delete = (table) => {
  return new knack_query(`DELETE FROM ${mysql.escapeId(table)}`)
}

const mysql_create_table = (table, if_not_exists = true) => {
  return if_not_exists === true
    ? new knack_table(`CREATE TABLE IF NOT EXISTS ${mysql.escapeId(table)} (`)
    : new knack_table(`CREATE TABLE ${mysql.escapeId(table)} (`)
}

module.exports = {
  update: mysql_update,
  insert: mysql_insert_into,
  select: mysql_select,
  drop:   mysql_delete,
  create: mysql_create_table,
  ops:    knack_where_ops,
  mysql:  mysql
}
