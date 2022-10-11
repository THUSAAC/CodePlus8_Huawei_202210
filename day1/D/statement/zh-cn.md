{{ self.title() }}

{{ s('description') }}

本题中，对于一个无重边自环的无向图，称图上的一条道路为**简单路**当且仅当其不经过重复节点。即，假设该道路经过的节点依次为 $(u_1,u_2,\cdots,u_k)$，则这条道路为简单路当且仅当 $u_1,u_2,\cdots,u_k$ 两两不同。

给出大质数 $P$ 和 $q$ 次询问，每组询问给出正整数 $n$，你需要求出满足以下所有条件的**有标号**无向图个数，对 $P$ 取模：

1. 图有 $n$ 个节点且不存在重边与自环；
2. 图上不存在边数为 3 的简单路，即图上无法找到四个两两不同的节点 $u_1,u_2,u_3,u_4$ 满足 $(u_1,u_2),(u_2,u_3),(u_3,u_4)$ 均在图中；
3. 在满足条件 1 和 2 的基础上，图的边数最多。

{{ s('input format') }}

{{ self.input_file() }}

输入的第一行包含两个正整数 $q$, $P$，保证 $q \le {{ tl.hn(args['q']) }}$，分别表示询问次数和模数。

接下来 $q$ 行每行包含一个正整数 $n$，保证 $n \le {{ tl.hn(args['n']) }}$，描述一次询问。

{{ s('output format') }}

{{ self.output_file() }}

对于每组询问输出一行一个非负整数，表示满足条件的有标号无向图个数对 $P$ 取模的值。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

以下样例解释将用 $1$ 到 $n$ 之间的整数给每个节点进行编号。

对于第一组询问，只有边集为 $\varnothing$ 的图满足条件。

对于第二组询问，其中两个满足条件的图的边集分别为 $\{(1,2)(2,3)(1,3)(4,5)(5,6)(4,6)\}$ 和 $\{(1,3)(3,5)(1,5)(2,4)(4,6)(2,6)\}$。

{{ s('subtasks') }}

对于全部数据，保证 $10^8\lt P\lt 10^9$ 且 $P$ 是素数。

{{ tbl('data') }}