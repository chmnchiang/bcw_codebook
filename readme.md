# CodeBook of Team bcw0x1bd2.

- use \lstinputlisting{filename.cpp} to include external file.
  
# TODO  
  
- vonoroi diagram / delaunay trangulation  
- 3D convex hull (N log N ?) 
- in/out center formula  
- 噁心 minkowski sum  
- steiner tree(?)  
- link-cut tree (change better example code)

# Alpha

| Contest       | Date          | Rank |   |   |   |   |   |   |   |   |   |   |   |   |   |
| ------------- |:-------------:|:----:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| ASC 47        | 2015/04/01    | 11 | **A** | B | _ | D | E | F | G | _ | _ | J |   |
| ASC 46        | 2015/04/12    | 34 | A | B | _ | **D** | E | F | G | _ | **I** | J |
| ASC 45        | 2015/04/25    | 25 | A | B | **C** | D | **E** | F | G | **H** | x | x | K |
| ASC 44        | 2015/05/03    | 17 | _ | B | C | D | E | F | **G** | H | I | x |
| ASC 43        | 2015/05/23    | 23 | **A** | B | **C** | **D** | E | **F**| G | H | I | J | K | L |
| ASC 42        | 2015/06/04    | 31 | . | . | C | D | . | F | G | . | **I** | J |
| ASC 41        | 2015/06/14    | 19 | A | **B** | . | D | E | . | G | H | I | J |
| ASC 40        | 2015/06/27    | 8 | A | B | C | **D** | E | F | G | H | I | . |
| ASC 39        | 2015/11/27    | 1 | A | B | C | D | E | (F) | G | H | I | J |
| ASC 38        | 2015/12/17    | 5 | A | B | C | D | E | **F** | **G** | H | **I** | J |
| ASC 37        | 2015/09/05    | | A | B | **C** | D | **E** | F | G | H | **I** |
| ASC 36        | 2015/08/15    | 34 | A | **B** | **C** | **D** | **E** | **F** | G | H | **I** | J |
| ASC 35        | 2015/12/20    | 8 | **A** | (B) | C | _ | E | F | G | H | **I** | J |
| ASC 34        | 2015/12/24    | 11 | **A** | B | C | (D) | E | F | **G** | H | I | J |
| ASC 33        | 2014/07/30    | 24 | A | B | **C** | **D** | E | F | . | H | . | J |
| ASC 32        | 2016/02/05    | 1 | A | B | C | D | E | F | G | H | I | J | K |
| ASC 31        | 2014/07/07    | 21 | A | B | . | **D** | E | F | G | . | I | . | K |
| ASC 30        | 2016/02/25    | 2 | A | B | C | D | E | F | G | H | I | J |
| ASC 29        | 2016/02/27    | 27 | A | B | C | **D** | **E** | F | **G** | H | I | **J** |
| ASC 28        | 2016/02/29    | 2 | A | B | C | D | E | F | G | H | I | J |
| BSUIR 2014    | 2015/08/22    | | A | B | C | D | E | F | G | H | I | J | K |
| JAG 2015 Spring | 2015/08/29  | | A | **B** | **C** | D | E | F | G | **H** | **I** | **J** | K | L |
| JAG 2015 Autumn | 2015/11/23  | 1 | A | B | C | D | E | F | G | H | . | J | K |
| Xian 2014       | 2015/09/13  | | A | **B**  | C |   | **E**  | F | **G**  | H | I | **J**  | K |
| NEERC 2011      | 2015/10/09  | | A | B | C | D | E | **F**  | G | .  | I | **J**  | K | **L** |
| Jakarta 2014    | 2015/10/24  | | A | B | C | D | E | F | G | H | I | J | K |
| Japan 2014      | 2015/10/31  | | A | B | C | D | E | F | G | H | I | J | **K**|
| Dhaka 2014      | 2015/11/14  | | A | B | C | **D** | E | F | G | H | I | J |
| Mudanjiang 2014 | 2015/11/22  | | A | B | x | D | E | F | **G** | H | I | . | **K** |
| Daejeon 2014    | 2015/11/28  | | **A** | B | C | D | E | F | G | H | I | J | K | **L** |
| NEERC Moscow 2015 | 2015/12/03| | A | **B** | C | D | E | _ | G | H | I | J | K | L |
| Singapore 2015  | 2015/12/10  | 2 | A | (B) | C | D | E | F | G | H | I | J | **K** |
| Shanghai 2015   | 2016/02/18  | 7 | A | B | **C** | D | **E** | F | G | _ | **I** | **J** | K | L |
| WF 2006         | 2016/02/19  | 1 | A | B | C | D | E | **F** | G | (H) | I | J |
| XVI Open Cup Saratov | 2016/02/21 | 32 | A | **B** | **C** | **D** | **E** | F | G | H | I | J | **K** |
| XVI Open Cup Bashkortostan | 2016/02/28 | 25 | A | **B** | C | D | E | F | **G** | H | I | J | **K** | L | **M** |
| WF 2007         | 2016/03/03  | 3 | A | B | **C** | D | (E) | F | G | (H) | I | **J** |
| XIV Open Cup Saratov | 2016/03/05 | 19 | . | B | C | **D** | E | F | . | _ | _ | J | K |
| WF 2008         | 2016/03/10  | 21 | A | B | . | . | **E** | F | **G** | **H** | I | J | K |
| IX Open Cup Saratov | 2016/03/12 | 10 | A | . | C | D | E | **F** | . | x | I | J |
| XVI Open Cup Tatarstan | 2016/03/13 | 8 | A | B | C | D | E | F | G | H | I | J | K | L | M |

- A : 賽內AC  
- **A** : 賽後AC  
- (A) : 精神AC  
- _ : 慘了了  
- x : 放棄
- . : 沒討論 
