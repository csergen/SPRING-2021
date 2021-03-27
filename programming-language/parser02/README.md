# PARSER
[Github](https://github.com/csergen/SPRING-2021/tree/main/programming-language/parser02)

## Step one:
- [Install docker on Linux](https://docs.docker.com/engine/install/)

## Step two:
```console 
  $ sudo run.sh

  or

  $ sudo systemctl start docker
  $ sudo docker build -t parser-img .
  $ sudo docker run -it --rm --name parser parser-img
  $ sudo systemctl stop docker.socket
```

### State Machine Diagram:
![smd](res/sm.png)

### Grammar:
```html
<program>: [int | void] main () <scope>

<sentences>: { <sentence> }

<sentence>: 
  <scope>       |
  <assign>      |
  <ifstmt>      |
  <forstmt>     |
  <whilestmt>   |

<type>:
  int | float | double | char | void

<id>: _a-Z
<number>: 0-9

<scope>: '{' <sentences> '}'

<assign>:
  [<type>] <id> ( = | += | -= | *= | /= ) <expression>

{* <conj> || <conj> || <conj> || ... *}
<expression>: <conj> { || <conj> }

{* <relation> && <relation> && <relation> && ... *}
<conj>: <relation> { && <relation> }

{* <addition> < <addition> <= <addition> > <addition> >= <addition> == <addition> != <addition>  .... *}
<relation>: <addition> { ( < | <= | > | >= | == | != ) <addition>}

{* <term> + <term> - <term> ..... *}
<addition>: <term> { (+ | -) <term> }

{* <negation> * <negation> / <negation> .... *}
<term>: <negation> { (* | /) <negation> }

{* !a | !0 *}
<negation>: ! <factor>

<factor>: <id> | <number> | <quote> | <dquote> 

<ifstmt>: if ({ <expression> }) <scope>
          { elseif ( { <expression> } ) <scope> }
          [ else <scope> ]

<forstmt>: for ([<assign>]; [<expression>]; [<assign>]) <scope>

<whilestmt>: while ( [<expression>] ) <scope>
```