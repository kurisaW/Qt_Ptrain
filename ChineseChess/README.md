## 详细文件点击此处[下载](https://pan.baidu.com/s/1MmzII7Xke0S-AMzI2RGXIQ?pwd=wdza)


## 系统架构说明
#### Main.cpp：

* ChooseDig:初始对话框（选择对战模式）
* ChooseDig:子窗体（根据所选的模式进入相应的模式界面）
* MainWnd:主窗体

>这里的signleGame、MultiGame、NetGame三个子类的父类为Board类，而Board类为棋盘类

#### SingleGame.h:

主要是人工智能的一些函数

#### MultiGame.h:

其实主要跟Board.h一样

#### NetGame.h:

主要是服务端与客户端的一些功能

#### ChooseDig:

主要决定我们创建的是signleGame、MultiGame、NetGame这三个中的窗口类型





## Board:

核心函数：

> ```
>       /* game data */
        Stone _s[32];				//32颗棋子
        int _r;						//指定的棋子半径、棋盘多大 : _r
        QPoint _off;				//偏移值
	    bool _bSide;				//指定的是红方还是黑方
> ```
---
> ```
> QVector<Step*> _steps;			//对走过的棋进行存储记录，主要用于悔棋
> ```

---

> ```
>     /* game status */		
>     int _selectid;				//选中棋子的ID
>     bool _bRedTurn;				//指目前是红方还是黑方走，True：红方
>     void init(bool bRedSide);	//摆棋，红棋在下
> ```

---

> ```
>     /* draw functions */
>     void paintEvent(QPaintEvent *);
>     void drawPlate(QPainter& p);	//绘制棋盘
>     void drawPlace(QPainter& p);	//绘制九宫格
>     void drawInitPosition(QPainter& p);//绘制初始位置
>     void drawInitPosition(QPainter& p, int row, int col);
>     void drawStone(QPainter& p);		//绘制棋子
>     void drawStone(QPainter& p, int id);
> ```

---

> ```
>     /* function for coordinate */		//坐标转换
>     QPoint center(int row, int col);	//行和列对应的棋盘像素坐标中心点
>     QPoint center(int id);				//某颗象棋的中心点
>     QPoint topLeft(int row, int col);	//获得左上角的中心点
>     QPoint topLeft(int id);
>     QRect cell(int row, int col);		//每一个格子对应的控制范围
>     QRect cell(int id);
> ```

---

> ```
>     bool getClickRowCol(QPoint pt, int& row, int& col); //点击的目标点，行和列
> ```

---

```
    /* help function */
    QString name(int id);				//棋子的id，比如车对应的0
    bool red(int id);					//看是红方还是黑方，红方：True
    bool sameColor(int id1, int id2);	//看是不是返回的相同的颜色
    int getStoneId(int row, int col);	//棋子的坐标
    void killStone(int id);				//被吃棋子的id
    void reliveStone(int id);			//复活棋子，用于悔棋
    void moveStone(int moveid, int row, int col); //更新移动棋子的到达坐标的行和列
    bool isDead(int id);				//判断这个id的棋子是不是被吃了
```

---

```
    /* move stone */
    void mouseReleaseEvent(QMouseEvent *);	//在鼠标松开时的一个回调函数
    void click(QPoint pt);					//mouseReleaseEvent调用的一个函数，表示点击的动作
    virtual void click(int id, int row, int col);//click的一个虚函数重载
    void trySelectStone(int id);			//点击的那颗棋子，表示我能不能点动
    void tryMoveStone(int killid, int row, int col);
    void moveStone(int moveid, int killid, int row, int col);//对移动信息的记录
    void saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps);	//把移动的棋子记录下来，以供将来悔棋的时候使用
    void backOne();				//悔棋一步
    void back(Step* step);		//悔棋多步
    virtual void back();		//一旦用户悔棋会调用这个函数
```

---

```
    /* rule */		//主要是象棋的移动规则
    bool canMove(int moveid, int killid, int row, int col);
    bool canMoveChe(int moveid, int killid, int row, int col);
    bool canMoveMa(int moveid, int killid, int row, int col);
    bool canMovePao(int moveid, int killid, int row, int col);
    bool canMoveBing(int moveid, int killid, int row, int col);
    bool canMoveJiang(int moveid, int killid, int row, int col);
    bool canMoveShi(int moveid, int killid, int row, int col);
    bool canMoveXiang(int moveid, int killid, int row, int col);
    
    bool canSelect(int id);		//红方还是黑方执子
```

---

```
    /* rule helper */
    int getStoneCountAtLine(int row1, int col1, int row2, int col2);//看这两个坐标有多少棋子
    int relation(int row1, int col1, int row, int col);		//两个坐标的关系
    bool isBottomSide(int id);			//看是不是在棋子的下面这一层
```

类：

#### Stone类(象棋棋子)：

```
class Stone
{
public:
    Stone();
    ~Stone();

    enum TYPE{CHE, MA, PAO, BING, JIANG, SHI, XIANG};

    void init(int id);

    int _row;		//行
    int _col;		//列
    TYPE _type;		//象棋的类型：车、马、炮
    bool _dead;		//棋子的死亡属性，看看有没有被杀
    bool _red;		//棋子的阵营
    int _id;		//32颗棋子的id	

    QString name(); //返回象棋的名字，主要用在绘制上

    void rotate();	//旋转棋盘，主要是客户端和服务端的界面旋转
};
```

#### Step类（走棋的记录）：

```
class Step : public QObject
{
    Q_OBJECT
public:
    explicit Step(QObject *parent = 0);
    ~Step();

    int _moveid;	//移动的棋子id
    int _killid;	//被吃棋子的id
    int _rowFrom;	//行初始坐标
    int _colFrom;	//列初始坐标
    int _rowTo;		//行目的坐标
    int _colTo;		//列目的坐标

signals:

public slots:
};
```
