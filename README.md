pg-dump-fcinfo
====

Have you ever wondered what is in `fcinfo` the `FunctionCallInfoBaseData` that
stores a C function's context in PostgreSQL.

> [Does PostgreSQL provide anything to dump fcinfo?](https://dba.stackexchange.com/q/302051/2639)

I did. This fixes that. Now you can find out the contextual differences between,

```sql
SELECT dump_fcinfo();
SELECT * FROM dump_fcinfo();
SELECT * FROM dump_fcinfo() LIMIT 5;
SELECT dump_fcinfo() FROM ( VALUES (1) ) AS t(x);
```

You can get a result like this,

```text
=# \x
Expanded display is on.

=# SELECT * FROM dump_fcinfo();
-[ RECORD 1 ]--------------+--
sfrm_valuepercall          | t
sfrm_materialize           | t
sfrm_materialize_random    | f
sfrm_materialize_preferred | t
fmgrinfo_fn_nargs          | 0
tupledescdata_natts        | 7
tupledescdata_strict       | t
```

Quesitons I've Answered (with help)
----

* Is `ValuePerCall` ever **not** set in `allowedMode`? Answer: no. (confirmed by RhodiumToad)
* Is `Materialize` ever **not** set in `allowedMode`? Answer: no.
* [Is `Materialize_Random` ever **not** set in `allowedMode`?](https://dba.stackexchange.com/q/302059/2639)

Installation
----

Build and install with,

```sh
make;
sudo make install;
echo "CREATE EXTENSION dump_fcinfo" | psql
```

Way more work
----

This only dumps the fields I was interested in there is far more stuff though.
As always, feel free to send patches and feature requests.

Raison d'être
----

This exists because I wanted to learn more about [`ValuePerCall` and
`Materialize` mode](https://dba.stackexchange.com/q/301920/2639). This
information is provided to your function by a [C Macro which provides the
function context](https://dba.stackexchange.com/q/302049/2639), naturally [I
wanted to see that context as I invoked the same function in different
places](https://dba.stackexchange.com/q/302051/2639)

Now you can see it it too by running 

* [`install_and_test`](./install_and_test)

Enjoy it?
====

Please consider endorsing Evan Carroll for PostgreSQL on LinkedIn. It's free,
and it helps me get clients.

* https://www.linkedin.com/in/evancarroll/
