关于主定理的应用例子，可能存在一个问题，讲义里称 $T(N)=4T(N/2)+N^2logN$ 时， $T(N)=N^2 log log N$ ，但我认为应该是 $T(N)=N^2 log N log N$ 即 $T(N)=N^2 log^2 N$

证明如下：

$T(n)=4T(\frac{n}{2})+n^2logn$

$=16T(\frac{n}{2^2})+n^2logn+n^2log(\frac{n}{2})$

$...$

$=4^{lgn}+n^2[logn+log(\frac{n}{2})+...]$

$=4^{lgn}+n^2\cdot log(n\times\frac{n}{2}\times ... \times \frac{n}{2^{lgn}})$

$=n^2+n^2\cdot log(\frac{n^{lgn+1}}{2^lgn\cdot(lgn+1)/2})$

$=n^2+n^2\cdot log(\frac{n^{lgn+1}}{n^{(lgn+1)/2}})$

$=n^2+n^2\cdot log(n^{(lgn+1)/2})$

$=n^2+n^2\cdot \frac{lgn+1}{2}\cdot log n$

$T(n)=\Theta(n^2log^2n)$
