数学公式

\paragraph{组合公式}\begin{enumerate}

	\item $\sum_{k=1}^{n}(2k-1)^2 = \frac{n(4n^2-1)}{3}	$
	\item $\sum_{k=1}^{n}k^3 = (\frac{n(n+1)}{2})^2	$
	\item $\sum_{k=1}^{n}(2k-1)^3 = n^2(2n^2-1)	$
	\item $\sum_{k=1}^{n}k^4 = \frac{n(n+1)(2n+1)(3n^2+3n-1)}{30}	$
	\item $\sum_{k=1}^{n}k^5 = \frac{n^2(n+1)^2(2n^2+2n-1)}{12}	$
	\item $\sum_{k=1}^{n}k(k+1) = \frac{n(n+1)(n+2)}{3}	$
	\item $\sum_{k=1}^{n}k(k+1)(k+2) = \frac{n(n+1)(n+2)(n+3)}{4} $
	\item $\sum_{k=1}^{n}k(k+1)(k+2)(k+3) = \frac{n(n+1)(n+2)(n+3)(n+4)}{5} $
	\item $\mbox{错排：}D_n = n!(1-\frac{1}{1!}+\frac{1}{2!}-\frac{1}{3!}+\ldots+\frac{(-1)^n}{n!}) = (n-1)(D_{n-2}-D_{n-1})$
\end{enumerate}

\paragraph{三角公式}\begin{enumerate}

	\item $\sin(\alpha \pm \beta) = \sin\alpha\cos\beta \pm \cos\alpha\sin\beta	$
	\item $\cos(\alpha \pm \beta) = \cos\alpha\cos\beta \mp \sin\alpha\sin\beta	$
	\item $\tan(\alpha \pm \beta) = \frac{\tan\alpha \pm \tan\beta}{1 \mp \tan\alpha\tan\beta}	$
	\item $\tan\alpha \pm \tan\beta = \frac{\sin(\alpha \pm \beta)}{\cos\alpha\cos\beta}	$
	\item $\sin\alpha+\sin\beta = 2\sin\frac{\alpha+\beta}{2}\cos\frac{\alpha-\beta}{2}	$
	\item $\sin\alpha-\sin\beta = 2\cos\frac{\alpha+\beta}{2}\sin\frac{\alpha-\beta}{2}	$
	\item $\cos\alpha+\cos\alpha = 2\cos\frac{\alpha+\beta}{2}\cos\frac{\alpha-\beta}{2}	$
	\item $\cos\alpha-\cos\beta = -2\sin\frac{\alpha+\beta}{2}\sin\frac{\alpha-\beta}{2}	$
	\item $\sin(n\alpha) = n\cos^{n-1}\alpha\sin\alpha-\binom{n}{3}\cos^{n-3}\alpha\sin^3\alpha+\binom{n}{5}\cos^{n-5}\alpha\sin^5\alpha-\ldots	$
	\item $\cos(n\alpha) = \cos^n\alpha-\binom{n}{2}\cos^{n-2}\alpha\sin^2\alpha+\binom{n}{4}\cos^{n-4}\alpha\sin^4\alpha-\ldots$
\end{enumerate}

\paragraph{三次方程求根公式}

\begin{align}
	& x^3+px+q=0		\nonumber\\
	& x_j=\omega^j\sqrt[3]{-\frac{q}{2}+\sqrt{(\frac{q}{2})^2+(\frac{p}{3})^3}}+\omega^{2j}\sqrt[3]{-\frac{q}{2}-\sqrt{(\frac{q}{2})^2+(\frac{p}{3})^3}}\nonumber\\
	& \mbox{其中}j=0,1,2\quad \omega=\frac{(-1+\mathrm{i}\sqrt{3})}{2}\nonumber	
\end{align}

当求解$a^3+bx^2+cx+d=0$时，令$x=y-\frac{b}{3a}$，再求解$y$，即转化为$x^3+px+q=0$的形式。

\paragraph{椭圆} \begin{enumerate}
	\item 椭圆$\frac{x^2}{a^2} + \frac{y^2}{b^2} = 1$, 其中离心率$e = \frac{c}{a}, c = \sqrt{a^2 - b^2}$; 焦点参数$p = \frac{b^2}{a}$
	\item 椭圆上$(x, y)$点处的曲率半径为$R = a^2 b^2 (\dfrac{x^2}{a^4} + \dfrac{y^2}{b^4})^\frac{3}{2} = \dfrac{(r_1 r_2)^\frac{3}{2}}{ab}$, 其中$r_1$和$r_2$分别为$(x, y)$与两焦点$F_1$和$F_2$的距离. 设点$A$和点$M$的坐标分别为$(a, 0)$和$(x, y)$, 则$AM$的弧长为
	\[ L_{AM} = a \int_0^{\arccos{\frac{x}{a}}} \sqrt{1 - e^2 \cos^2 t} \textrm{d} t = a \int_{\arccos{\frac{x}{a}}}^\frac{\pi}{2} \sqrt{1 - e^2 \sin^2 t} \textrm{d} t\]
	\item 椭圆的周长$L = 4a \int_0^{\frac{\pi}{2}} \sqrt{1 - e^2 \sin^2 t } \textrm{d} t = 4a E(e, \frac{\pi}{2})$, 其中
	\[ E(e, \frac{\pi}{2}) = \frac{\pi}{2} [ 1 - (\frac{1}{2})^2 e^2 - (\frac{1 \times 3}{2 \times 4})^2 \frac{e^4}{3} - (\frac{1 \times 3 \times 5}{2 \times 4 \times 6})^2 \frac{e^6}{5} - \cdots\]
	\item 设椭圆上点$M(x, y), N(x, -y), x, y > 0, A(a, 0)$, 原点$O(0, 0)$, 扇形$OAM$的面积$S_{OAM} = \frac{1}{2} ab \arccos{\frac{x}{a}}$, 弓形$MAN$的面积$S_{MAN} = ab \arccos{\frac{x}{a}} - xy$.
	\item 需要$5$个点才能确定一个圆锥曲线.
	\item 设$\theta$为$(x, y)$点关于椭圆中心的极角, $r$为$(x, y)$到椭圆中心的距离, 椭圆极坐标方程:
	\[ x = r \cos \theta, y = r \sin \theta, r^2 = \frac{b^2 a^2}{b^2 \cos^2 \theta + a^2 \sin^2 \theta}\]
\end{enumerate}

\paragraph{抛物线} \begin{enumerate}
	\item 标准方程$y^2 = 2px$, 曲率半径$ R = \dfrac{(p + 2x)^{\frac{3}{2}}}{\sqrt{p}}$
	\item 弧长: 设$M(x, y)$是抛物线上一点, 则$L_{OM} = \frac{p}{2} [ \sqrt{\frac{2x}{p}(1 + \frac{2x}{p})} + \ln(\sqrt{\frac{2x}{p}} + \sqrt{1 + \frac{2x}{p}})]$
	\item 弓形面积: 设$M, D$是抛物线上两点, 且分居一, 四象限. 做一条平行于$MD$且与抛物线相切的直线$L$. 若$M$到$L$的距离为$h$. 则有$S_{MOD} = \frac{2}{3}MD \cdot h$.
\end{enumerate}

\paragraph{重心} \begin{enumerate}
	\item 半径$r$, 圆心角为$\theta$的扇形的重心与圆心的距离为$\dfrac{4r\sin\frac{\theta}{2}}{3\theta}$.
	\item 半径$r$, 圆心角为$\theta$的圆弧的重心与圆心的距离为$\dfrac{4r\sin^3\frac{\theta}{2}}{3(\theta - \sin\theta)}$.
	\item 椭圆上半部分的重心与圆心的距离为$\dfrac{4b}{3\pi}$.
	\item  抛物线中弓形$MOD$的重心满足$CQ = \frac{2}{5} PQ$, $P$是直线$L$与抛物线的切点, $Q$在$MD$上且$PQ$平行$x$轴, $C$是重心.
\end{enumerate}

\paragraph{向量恒等式} \begin{enumerate}
	\item $\vec{a} \cdot (\vec{b} \times \vec{c}) = \vec{b} \cdot (\vec{c} \times \vec{a}) = \vec{c} \cdot (\vec{a} \times \vec{b})$.
	\item $\vec{a} \times (\vec{b} \times \vec{c}) = (\vec{c} \times \vec{b}) \times \vec{a} = \vec{b}(\vec{a} \cdot \vec{c}) - \vec{c}(\vec{a} \cdot \vec{b})$.
\end{enumerate}

\paragraph{平面几何常用公式} \begin{enumerate}

	\item 四边形: 设$D_1, D_2$为对角线, $M$为对角线中点连线, $A$为对角线夹角 \begin{enumerate}
		\item $a^2 + b^2 + c^2 + d^2 = D_1^2 + D_2 ^ 2 + 4 M^2$
		\item $S = \frac{1}{2} D_1  D_2 \sin A$
		\item $ac + bd = D_1 D_2$ (内接四边形适用)
		\item $S = \sqrt{(p - a)(p - b)(p - c)(p - d)}, p$为半周长 (内接四边形适用)
	\end{enumerate}
	\item 棱台: \begin{enumerate}
		\item 体积$V = \dfrac{(A_1 + A_2 + \sqrt{A_1 A_2}) \cdot h}{3}$, $A_1, A_2$分别为上下底面面积, $h$为高.
		\item 侧面积$S = \frac{1}{2} (p_1 + p_2) \cdot l$, $p_1, p_2$为上下底面周长, $l$为斜高. (正棱台适用)
	\end{enumerate}
\end{enumerate}

\paragraph{树的计数} \begin{enumerate}
	\item 有根数计数: 令$S_{n, j} = \sum\limits_{1 \le i \le n / j} a_{n + 1 - ij} = S_{n - j, j} + a_{n + 1 - j}$.\\
		于是, $n + 1$个结点的有根数的总数为$a_{n + 1} = \dfrac{\sum\limits_{1 \le j \le n} j \cdot a_j \cdot S_{n, j} }{n}$.\\
		附: $a_1 = 1, a_2 = 1, a_3 = 2, a_4 = 4, a_5 = 9, a_6 = 20, a_9 = 286, a_{11} = 1842$
	\item 无根树计数: 当$n$是奇数时, 则有$a_n - \sum\limits_{1 \le i \le \frac{n}{2}} a_i a_{n - i}$种不同的无根树.\\
		当$n$是偶数时, 则有$a_n - \sum\limits_{1 \le i \le \frac{n}{2}} a_i a_{n - i} + \dfrac{1}{2} a_\frac{n}{2} (a_\frac{n}{2} + 1)$种不同的无根树.
	\item 完全图的生成树个数: $n^{n - 2}$
	\item Matrix-Tree定理: 对任意图$G$, 设mat[$i$][$i$] = $i$的度数, mat[$i$][$j$] = $i$与$j$之间边数的相反数, 则mat[$i$][$j$]的任意余子式的行列式就是该图的生成树个数.
\end{enumerate}

