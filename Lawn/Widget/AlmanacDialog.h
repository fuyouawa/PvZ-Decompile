#ifndef __ALMANACDIALOG_H__
#define __ALMANACDIALOG_H__

#include "LawnDialog.h"
#include "../../ConstEnums.h"
#include "../../SexyAppFramework/SliderListener.h"
#include "../../SexyAppFramework/Slider.h"

// 图鉴中植物显示的位置常量
constexpr const float			ALMANAC_PLANT_POSITION_X		= 578.0f;  // 植物X坐标
constexpr const float			ALMANAC_PLANT_POSITION_Y		= 140.0f;  // 植物Y坐标
constexpr const float			ALMANAC_ZOMBIE_POSITION_X		= 559.0f;  // 僵尸X坐标
constexpr const float			ALMANAC_ZOMBIE_POSITION_Y		= 175.0f;  // 僵尸Y坐标
constexpr const int				ALMANAC_INDEXPLANT_POSITION_X	= 167;     // 索引页面植物X坐标
constexpr const int				ALMANAC_INDEXPLANT_POSITION_Y	= 255;     // 索引页面植物Y坐标
constexpr const float			ALMANAC_INDEXZOMBIE_POSITION_X	= 535.0f;  // 索引页面僵尸X坐标
constexpr const float			ALMANAC_INDEXZOMBIE_POSITION_Y	= 215.0f;  // 索引页面僵尸Y坐标
constexpr const int				ALMANAC_DESCRIPTION_MIN_HEIGHT	= 20;      // 描述文本最小高度
constexpr const int				WEIRD_CHARACTERS_COUNT			= 1;       // 特殊字符数量

// 前向声明
class Plant;
class Zombie;
class LawnApp;
class GameButton;
class Reanimation;
class Slider;

// 图鉴对话框类,继承自LawnDialog和SliderListener
class AlmanacDialog : public LawnDialog, public Sexy::SliderListener
{
private:
	// 图鉴按钮ID枚举
	enum
	{
		ALMANAC_BUTTON_CLOSE,    // 关闭按钮
		ALMANAC_BUTTON_PLANT,    // 植物按钮
		ALMANAC_BUTTON_ZOMBIE,   // 僵尸按钮
		ALMANAC_BUTTON_INDEX,    // 索引按钮
		ALMANAC_BUTTON_NEXT,     // 下一页按钮
		ALMANAC_BUTTON_LAST      // 上一页按钮
	};

public:
	LawnApp*					mApp;                   // 游戏应用指针
	GameButton*					mCloseButton;           // 关闭按钮
	GameButton*					mIndexButton;           // 索引按钮
	GameButton*					mPlantButton;           // 植物按钮
	GameButton*					mZombieButton;          // 僵尸按钮
	Sexy::Slider*				mPlantSlider;           // 植物列表滚动条
	Sexy::Slider*				mZombieSlider;          // 僵尸列表滚动条
	AlmanacPage					mOpenPage;              // 当前打开的页面
	Reanimation*				mReanim[4];             // 动画数组
	SeedType					mSelectedSeed;          // 选中的植物类型
	ZombieType					mSelectedZombie;        // 选中的僵尸类型
	Plant*						mPlant;                 // 当前显示的植物
	Zombie*						mZombie;                // 当前显示的僵尸
	Zombie*						mZombiePerfTest[400];   // 僵尸性能测试数组
	float						mIncrement;             // 增量值
	float						mScrollPosition;        // 滚动位置
	float						mScrollAmount;          // 滚动量
	const float					mBaseScrollSpeed = 1.0f; // 基础滚动速度
	const float					mScrollAccel = 0.1f;    // 滚动加速度
	float						mMaxScrollPosition;     // 最大滚动位置
	int							mLastMouseX;            // 鼠标最后X坐标
	int							mLastMouseY;            // 鼠标最后Y坐标
	bool						mIsOverDescription;     // 是否在描述区域上
	int							mDescriptionLineSpacing; // 描述文本行间距
	float						mDescriptionScroll;     // 描述文本滚动位置
	float						mDescriptionMaxScroll;  // 描述文本最大滚动位置
	float						mDescriptionOffsetScroll; // 描述文本偏移滚动量
	float						mDescriptionOffsetY;    // 描述文本Y偏移
	bool						mDescriptionOverfill;   // 描述文本是否溢出
	Rect						mDescriptionRect;       // 描述文本区域
	Rect						mDescriptionSliderRect; // 描述文本滚动条区域
	bool						mDescriptionSliderDragging; // 是否正在拖动描述文本滚动条

public:
	// 构造函数和析构函数
	AlmanacDialog(LawnApp* theApp);
	virtual ~AlmanacDialog();

	// 清理对象
	void						ClearObjects();
	// 从管理器移除时的处理
	virtual void				RemovedFromManager(WidgetManager* theWidgetManager);
	// 添加到管理器时的处理
	virtual void				AddedToManager(WidgetManager* theWidgetManager);
	// 滚动条值改变时的处理
	void                        SliderVal(int theId, double theVal);
	// 设置植物
	void						SetupPlant();
	// 设置僵尸
	void						SetupZombie();
	// 设置页面
	void						SetPage(AlmanacPage thePage);
	// 更新
	virtual void				Update();
	// 绘制索引页面
	void						DrawIndex(Graphics* g);
	// 绘制植物页面
	void						DrawPlants(Graphics* g);
	// 绘制僵尸页面
	void						DrawZombies(Graphics* g);
	// 绘制
	virtual void				Draw(Graphics* g);
	// 获取植物位置
	void						GetSeedPosition(SeedType theSeedType, int& x, int& y);
	// 植物点击检测
	SeedType					SeedHitTest(int x, int y);
	// 检查僵尸是否有剪影
	/*inline*/ int				ZombieHasSilhouette(ZombieType theZombieType);
	// 检查僵尸是否显示
	int							ZombieIsShown(ZombieType theZombieType);
	// 检查僵尸是否有描述
	int							ZombieHasDescription(ZombieType theZombieType);
	// 获取僵尸位置
	void						GetZombiePosition(ZombieType theZombieType, int& x, int& y);
	// 僵尸点击检测
	ZombieType					ZombieHitTest(int x, int y);
	// 鼠标抬起处理
	virtual void				MouseUp(int x, int y, int theClickCount);
	// 鼠标按下处理
	virtual void				MouseDown(int x, int y, int theClickCount);
	// 鼠标拖动处理
	virtual void				MouseDrag(int x, int y);
	// 键盘字符输入处理
	virtual void				KeyChar(char theChar) {  }

	// 获取僵尸类型
	static ZombieType			GetZombieType(int theIndex);
	// 显示植物
	/*inline*/ void				ShowPlant(SeedType theSeedType);
	// 显示僵尸
	/*inline*/ void				ShowZombie(ZombieType theZombieType);
	// 鼠标滚轮处理
	virtual void				MouseWheel(int theDelta);

	// 翻译和清理字符串
	SexyString					TranslateAndSanitize(SexyString str);
};

// 全局变量:记录已击败的僵尸类型
extern int gZombieDefeated[NUM_ZOMBIE_TYPES];

// 初始化玩家图鉴
/*inline*/ void					AlmanacInitForPlayer();
// 记录玩家击败的僵尸
/*inline*/ void					AlmanacPlayerDefeatedZombie(ZombieType theZombieType);

#endif
