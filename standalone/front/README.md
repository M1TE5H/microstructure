# Front

**Note:** This idea requires significant further consideration; this gimmicky sub-project exists only to start a conversation about easing the entry into `C++` for scientific software developers and providing a more intuitive alternative syntax.

The `front` is a simple syntax-to-syntax compiler to convert custom `microstructure` methods into standard `C++23` functions.

The `microstructure` method syntax is designed with the research scientist end-user in mind; the syntax pertains exclusively to the function identifiers and the function parameters in the function signature. For lack of better terminology, the `front` preprocesses a pseudocode-like function signature syntax that contains "cleaved" identifiers and "demarcated" arguments. That is, the function identifier is "cleaved" into sub-identifiers (which will be reconstituted into single/unique identifier) that can appear before "demarcated" arguments in an ordered sequence.

In general, a function signature in the `microstructure` syntax can be written as
```
return_type name1 ( {params1} ) name2 ( {params2} ) ... ;
```
which the `front` compiles into
```
return_type name1name2... ( {params1}, {params2}, ... );
```
The former syntax could allow applications that rely on the framework to be developed with a more intuitve client-facing interface.

Consider the following examples:

| Custom Syntax | Standard Syntax[^1] |
|---|---|
| `auto transform ( vector v ) with ( matrix m );` | `auto transform@with ( vector v, matrix m );` |
| `auto add ( nucleus n... ) with ( distribution d... ) in ( ensemble e ); ` | `auto add@with@in ( nucleus n..., distribution d, ensemble e );` |
| `auto evolve ( state s ) at ( condition c ) over ( time t ) ` | `auto evolve@at@over( state s, condition c, time t );` |
| `auto create ( visualisation v ) of ( simulation s ) with ( drawer d )` | ` create@of@with ( visualisation v, simulation s, drawer d )` |

[^1]: Note that `@` is a placeholder unifier to merge the subidentifiers into one identifier for standard `C++` compilation.