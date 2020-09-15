// Includes, namespace and prototypes
#include "template.h"
using namespace AGK;
app App;

//屏幕分辨率参数
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
//图像索引
const int TITLE_IMAGE=1;
const int INTRO_IMAGE=2;
const int FARM_IMAGE=3;
const int EGG_IMAGE=4;
const int VULTRUE_IMAGE=5;
const int BASKET_IMAGE=6;
const int BROKEN_EGG_IMAGE=7;
const int HIT_BASKET_IMAGE=8;
//精灵索引
const int TITLE_SPRITE=1;
const int INTRO_SPRITE=2;
const int FARM_SPRITE=3;
const int EGG_SPRITE=4;
const int VULTRUE_SPRITE=5;
const int BASKET_SPRITE=6;
const int BROKEN_EGG_SPRITE=7;
const int HIT_BASKET_SPRITE=8;
//音乐索引
const int INTRO_MUSIC=1;
const int MAIN_MUSIC=2;
//声音索引
const int POP_SOUND=1;
const int BROKEN_SOUND=2;
const int TYPE_SOUND=3;
const int COMPLETE_SOUND=4;
const int PERFECT_SOUND=5;
//动画帧
const int FRAME_WIDTH=120;
const int FRAME_HEIGHT=110;
const int FRAME_COUNT=8;
const int FRAME_PER_SECOND=8;

//移动距离
const float VULTRUE_MOVE=2;
const float BASKET_MOVE=4;

//蛋下落的加速度
const float ACCELERATION=0.008f;

const int MAX_EGGS=40;//蛋的总数
const int CLONE_EGG=100;//用于小蛋的索引

//文本索引
const int GAME_OVER_TEXT=1;
const int RESULT_TEXT=2;
const int EGG_CAUGHT_TEXT=3;
const int EGG_MISSED_TEXT=4;
const int SCORE_TEXT=5;
const int CAUGHT_MULTIPLIER_TEXT=6;
const int MISSED_MULTIPLIER_TEXT=7;
const int PERFECT_SCORE_TEXT=8;

//文本的大小
const int TEXT_SIZE=36;

//游戏状态
const int GAME_STARTED=1;
const int GAME_INTRO=2;
const int GAME_IN_PLAY=3;
const int GAME_OVER=4;
const int GAME_SUMMARY=5;
int gameState=GAME_STARTED;//游戏的初始状态


//界面时间
const int INTRO_TIME=5;
const int GAME_OVER_TIME=4;
const int GAME_SUMMARY_TIME=5;

//其他参数
int g_eggs=MAX_EGGS;//剩余蛋数
int eggs_Missed=0;//打碎的鸡蛋数
int eggs_Caught=0;//接住的鸡蛋数
int g_Score=0;//总共得分
int g_time=0;//下落的时间
int g_summaryComplete = 0;//游戏总结
const int SCORE_MULTIPLIER  = 1000;//一个鸡蛋1000分

void app::Begin( void )
{
	//设置屏幕、标题
	agk::SetWindowTitle("Vulture Trouble");
	agk::SetVirtualResolution(SCREEN_WIDTH,SCREEN_HEIGHT);
	//加载图像
	agk::LoadImage(TITLE_IMAGE,"Vulture Trouble/titleScreen.png");
	agk::LoadImage(INTRO_IMAGE,"Vulture Trouble/intro.png");
	agk::LoadImage(FARM_IMAGE,"Vulture Trouble/farm.png");
	agk::LoadImage(EGG_IMAGE,"Vulture Trouble/egg.png");
	agk::LoadImage(VULTRUE_IMAGE,"Vulture Trouble/vulture.png");
	agk::LoadImage(BASKET_IMAGE,"Vulture Trouble/basket.png");
	agk::LoadImage(BROKEN_EGG_IMAGE,"Vulture Trouble/brokenEgg.png");
	agk::LoadImage(HIT_BASKET_IMAGE,"Vulture Trouble/hitBasket.png");
	//创建精灵
	agk::CreateSprite(TITLE_SPRITE,TITLE_IMAGE);
	agk::CreateSprite(INTRO_SPRITE,INTRO_IMAGE);
	agk::CreateSprite(FARM_SPRITE,FARM_IMAGE);
	agk::CreateSprite(EGG_SPRITE,EGG_IMAGE);
	agk::CreateSprite(VULTRUE_SPRITE,VULTRUE_IMAGE);
	agk::CreateSprite(BASKET_SPRITE,BASKET_IMAGE);
	agk::CreateSprite(BROKEN_EGG_SPRITE,BROKEN_EGG_IMAGE);
	agk::CreateSprite(HIT_BASKET_SPRITE,HIT_BASKET_IMAGE);
	//加载音乐
	agk::LoadMusic(INTRO_MUSIC,"Vulture Trouble/vultureLevel.mp3");
	agk::LoadMusic(MAIN_MUSIC,"Vulture Trouble/vultureTrouble.mp3");
	//加载声音
	agk::LoadSound(POP_SOUND,"Vulture Trouble/pop.wav");
	agk::LoadSound(BROKEN_SOUND,"Vulture Trouble/clap.wav");
	agk::LoadSound(TYPE_SOUND,"Vulture Trouble/type.wav");
	agk::LoadSound(COMPLETE_SOUND,"Vulture Trouble/complete.wav");
	agk::LoadSound(PERFECT_SOUND,"Vulture Trouble/vulturePerfect.wav");
	//设置动画帧
	agk::SetSpriteAnimation(VULTRUE_SPRITE,FRAME_WIDTH,FRAME_HEIGHT,FRAME_COUNT);

	//设置精灵位置,秃鹰位于屏幕顶部中心、篮子位于屏幕底部中心、鸡蛋位于秃鹰嘴部
	float vultrueX=SCREEN_WIDTH/2-agk::GetSpriteWidth(VULTRUE_SPRITE)/2;
	float vultrueY=0;
	agk::SetSpritePosition(VULTRUE_SPRITE,vultrueX,vultrueY);

	float basketX=SCREEN_WIDTH/2-agk::GetSpriteWidth(BASKET_SPRITE)/2;
	float basketY=SCREEN_HEIGHT-agk::GetSpriteHeight(BASKET_SPRITE);
	agk::SetSpritePosition(BASKET_SPRITE,basketX,basketY);

	float eggX=vultrueX;
	float eggY=vultrueY+agk::GetSpriteHeight(EGG_SPRITE)*1.9;
	agk::SetSpritePosition(EGG_SPRITE,eggX,eggY);

	//隐藏精灵
	agk::SetSpriteVisible(TITLE_SPRITE,0);
	agk::SetSpriteVisible(INTRO_SPRITE,0);
	agk::SetSpriteVisible(FARM_SPRITE,0);
	agk::SetSpriteVisible(EGG_SPRITE,0);
	agk::SetSpriteVisible(VULTRUE_SPRITE,0);
	agk::SetSpriteVisible(BASKET_SPRITE,0);
	agk::SetSpriteVisible(BROKEN_EGG_SPRITE,0);
	agk::SetSpriteVisible(HIT_BASKET_SPRITE,0);


	//在屏幕顶部设置一排小蛋,显示游戏剩余的蛋数(40)
	for(int i=0;i<MAX_EGGS;i++)
	{
		int clone=CLONE_EGG+i;//新蛋的索引
		float scale=0.5;
		agk::CloneSprite(clone,EGG_SPRITE);//克隆
		agk::SetSpriteScale(clone,scale,scale);//缩小蛋
		//设置小蛋的位置
		float x=agk::GetSpriteWidth(clone)*i;
		float y=0.0f;
		agk::SetSpritePosition(clone,x,y);
	}

	//创建文本
	agk::CreateText(GAME_OVER_TEXT,"GAME OVER");
	agk::CreateText(RESULT_TEXT,"GAME RESULTS");
	agk::CreateText(EGG_CAUGHT_TEXT,agk::Str(eggs_Caught));
	agk::CreateText(EGG_MISSED_TEXT,agk::Str(eggs_Missed));
	agk::CreateText(CAUGHT_MULTIPLIER_TEXT," X ");
	agk::CreateText(MISSED_MULTIPLIER_TEXT," X ");
	agk::CreateText(SCORE_TEXT,agk::Str(g_Score));
	agk::CreateText(PERFECT_SCORE_TEXT,"PERFECT SCORE!");


	//设置文本的大小
	agk::SetTextSize(GAME_OVER_TEXT,TEXT_SIZE);
	agk::SetTextSize(EGG_CAUGHT_TEXT,TEXT_SIZE);
	agk::SetTextSize(EGG_MISSED_TEXT,TEXT_SIZE);
	agk::SetTextSize(SCORE_TEXT,TEXT_SIZE);
	agk::SetTextSize(RESULT_TEXT,TEXT_SIZE);
	agk::SetTextSize(CAUGHT_MULTIPLIER_TEXT,TEXT_SIZE);
	agk::SetTextSize(MISSED_MULTIPLIER_TEXT,TEXT_SIZE);
	agk::SetTextSize(PERFECT_SCORE_TEXT,TEXT_SIZE);


	//设置文本的位置
	float gameOverX=SCREEN_WIDTH/2-agk::GetTextTotalWidth(GAME_OVER_TEXT)/2;//game over
	float gameOverY=SCREEN_HEIGHT/2-agk::GetTextTotalHeight(GAME_OVER_TEXT)/2;
	agk::SetTextPosition(GAME_OVER_TEXT,gameOverX,gameOverY);

	float resultX=SCREEN_WIDTH/2-agk::GetTextTotalWidth(RESULT_TEXT)/2;  //game result
	float resultY=SCREEN_HEIGHT/6-agk::GetTextTotalHeight(RESULT_TEXT)/2;
	agk::SetTextPosition(RESULT_TEXT,resultX,resultY);

	float eggCaughtX=SCREEN_WIDTH/4-agk::GetTextTotalWidth(EGG_CAUGHT_TEXT)/2; //接住的鸡蛋
	float eggCaughtY=SCREEN_HEIGHT/2-agk::GetTextTotalHeight(EGG_CAUGHT_TEXT)/2;
	agk::SetTextPosition(EGG_CAUGHT_TEXT,eggCaughtX,eggCaughtY);

	float eggMissedX=SCREEN_WIDTH-SCREEN_WIDTH/4;
	float eggMissedY=SCREEN_HEIGHT/2-agk::GetTextTotalHeight(EGG_MISSED_TEXT)/2;//打碎的鸡蛋
	agk::SetTextPosition(EGG_MISSED_TEXT,eggMissedX,eggMissedY);

	float scoreX=SCREEN_WIDTH/2-agk::GetTextTotalWidth(SCORE_TEXT)/2;//总共得分
	float scoreY=SCREEN_HEIGHT-agk::GetTextTotalHeight(SCORE_TEXT)*4;
	agk::SetTextPosition(SCORE_TEXT,scoreX,scoreY);

	//完美得分
	float perfectScoreTextX = SCREEN_WIDTH / 2 - agk::GetTextTotalWidth(PERFECT_SCORE_TEXT) / 2;
	float perfectScoreTextY = SCREEN_HEIGHT - agk::GetTextTotalHeight(SCORE_TEXT) * 2;
	agk::SetTextPosition(PERFECT_SCORE_TEXT, perfectScoreTextX, perfectScoreTextY);

	//接住鸡蛋的多行文本
	float caughtMultiplierTextX = SCREEN_WIDTH / 4;
	float caughtMultiplierTextY = SCREEN_HEIGHT / 2 - agk::GetTextTotalHeight(CAUGHT_MULTIPLIER_TEXT) / 2;
	agk::SetTextPosition(CAUGHT_MULTIPLIER_TEXT, caughtMultiplierTextX, caughtMultiplierTextY);

	//丢失鸡蛋的多行文本
	float missedMultiplierTextX = SCREEN_WIDTH - SCREEN_WIDTH / 3;
	float missedMultiplierTextY = SCREEN_HEIGHT / 2 - agk::GetTextTotalHeight(MISSED_MULTIPLIER_TEXT) / 2;
	agk::SetTextPosition(MISSED_MULTIPLIER_TEXT, missedMultiplierTextX, missedMultiplierTextY);

	//隐藏文本
	agk::SetTextVisible(GAME_OVER_TEXT,0);
	agk::SetTextVisible(RESULT_TEXT,0);
	agk::SetTextVisible(EGG_CAUGHT_TEXT,0);
	agk::SetTextVisible(EGG_MISSED_TEXT,0);
	agk::SetTextVisible(SCORE_TEXT,0);
	agk::SetTextVisible(PERFECT_SCORE_TEXT,0);
	agk::SetTextVisible(CAUGHT_MULTIPLIER_TEXT,0);
	agk::SetTextVisible(MISSED_MULTIPLIER_TEXT,0);
}


void app::Loop( void )
{
	switch(gameState)
	{
	case GAME_STARTED:
		//显示标题界面
		displayTitle();

		//是否按下Enter键
		if(agk::GetRawKeyPressed(AGK_KEY_ENTER))
		{
			hideTitle();
		}
		break;

	case GAME_INTRO:
		displayIntro();//显示介绍界面
		if(agk::Timer() >= INTRO_TIME)
		{
			hideIntro();//隐藏
		}
		break;

	case GAME_IN_PLAY:
		playGame();//玩游戏
		if(g_eggs <= 0)//判断剩余蛋数是否为0 
		{
			hideGame();//隐藏游戏
		}
		break;

	case GAME_OVER:
		showGameOver();
		if(agk::Timer() >= GAME_OVER_TIME)
		{
			hideGameOver();
		}
		break;

	case GAME_SUMMARY:
		displaySummary();
		if(agk::Timer() >= GAME_SUMMARY_TIME)
		{
			hideSummary();
		}
		break;
	}

	//刷新屏幕
	agk::Sync();
}


void app::End( void )
{

}

//显示标题界面
void app::displayTitle()
{
	if(!agk::GetSpriteVisible(TITLE_SPRITE))//如果标题界面不可视，可视
	{
		agk::SetSpriteVisible(TITLE_SPRITE,1);
	}

	if(!agk::GetMusicPlaying())//如果没有播放音乐，则循环播放音乐
	{
		agk::PlayMusic(INTRO_MUSIC,1,INTRO_MUSIC,INTRO_MUSIC);
	}
}

//隐藏标题界面
void app::hideTitle()
{
	agk::SetSpriteVisible(TITLE_SPRITE,0);
	agk::ResetTimer();//重置定时器
	gameState=GAME_INTRO;//改变游戏状态
}

//显示介绍界面
void app::displayIntro()
{
	if(!agk::GetSpriteVisible(INTRO_SPRITE))
	{
		agk::SetSpriteVisible(INTRO_SPRITE,1);//介绍界面可视化
	}

	if(agk::GetMusicPlaying() != MAIN_MUSIC)
	{
		agk::PlayMusic(MAIN_MUSIC,1,MAIN_MUSIC,MAIN_MUSIC);//循环播放主音乐
	}
}


//隐藏介绍界面
void app::hideIntro()
{
	agk::SetSpriteVisible(INTRO_SPRITE,0);//隐藏介绍界面

	agk::SetSpriteVisible(FARM_SPRITE,1);
	agk::SetSpriteVisible(VULTRUE_SPRITE,1);
	agk::SetSpriteVisible(BASKET_SPRITE,1);
	agk::SetSpriteVisible(EGG_SPRITE,1);

	//显示一排小蛋
	for(int i=0;i<MAX_EGGS;i++)
	{
		int clone=CLONE_EGG+i;
		agk::SetSpriteVisible(clone,1);
	}

	gameState=GAME_IN_PLAY;//改变游戏状态
}

//开始玩游戏
void app::playGame()
{	
	basketMove();//更新篮子的位置
	vultrueMove();//更新秃鹰的位置
	eggMove();//更新鸡蛋的位置
	checkCollision();//检测精灵碰撞
}



//秃鹰在屏幕顶部上方来回移动
void app::vultrueMove()
{
	//播放动画帧
	if(!agk::GetSpritePlaying(VULTRUE_SPRITE))
	{
		agk::PlaySprite(VULTRUE_SPRITE,FRAME_PER_SECOND);
	}

	float vultrueX=agk::GetSpriteX(VULTRUE_SPRITE);//获取当前秃鹰的x位置
	float vultrueWidth=agk::GetSpriteWidth(VULTRUE_SPRITE);//获取秃鹰的宽度

	if(vultrueX <= 0)//到达最左边
	{
		agk::SetSpriteFlip(VULTRUE_SPRITE,0,1);//垂直方向上翻转秃鹰
		agk::SetSpriteAngle(VULTRUE_SPRITE,180.0f);//中心旋转180度
	}
	if(vultrueX >= SCREEN_WIDTH-vultrueWidth)//到达最右边
	{
		agk::SetSpriteFlip(VULTRUE_SPRITE,0,0);
		agk::SetSpriteAngle(VULTRUE_SPRITE,0.0f);//返回原来的0度
	}                                                          

	if(agk::GetSpriteAngle(VULTRUE_SPRITE) == 180.0f)//向右
	{
		vultrueX+=VULTRUE_MOVE;
	}
	else//向左
	{
		vultrueX-=VULTRUE_MOVE;
	}

	agk::SetSpriteX(VULTRUE_SPRITE,vultrueX);//设置秃鹰的x位置
}


//用户通过左右按键 移动篮子的位置（x位置）
void app::basketMove()
{
	float basketX=agk::GetSpriteX(BASKET_SPRITE);
	float basketWidth=agk::GetSpriteWidth(BASKET_SPRITE);//篮子的宽度

	if(agk::GetRawKeyState(AGK_KEY_LEFT))//是否有左键按下
	{
		if(basketX <= 0)//是否达到左边界
		{
			basketX=0;
		}
		else
		{
			basketX-=BASKET_MOVE;
		}
	}

	if(agk::GetRawKeyState(AGK_KEY_RIGHT))//是否有右键按下
	{
		if(basketX >= SCREEN_WIDTH-basketWidth)
		{
			basketX=SCREEN_WIDTH-basketWidth;
		}
		else
		{
			basketX+=BASKET_MOVE;
		}
	}

	agk::SetSpriteX(BASKET_SPRITE,basketX);//刷新篮子的x位置
}


//更新鸡蛋的位置
void app::eggMove()
{
	float eggX=agk::GetSpriteX(VULTRUE_SPRITE);//鸡蛋的x位置与秃鹰位置有关
	float eggY=agk::GetSpriteY(EGG_SPRITE);
	float eggWidth=agk::GetSpriteWidth(EGG_SPRITE);
	float distance;

	//鸡蛋的初始位置位于秃鹰的嘴的下面
	if(agk::GetSpriteAngle(VULTRUE_SPRITE) == 180.0f)//秃鹰朝右时
	{
		eggX=agk::GetSpriteX(VULTRUE_SPRITE)+agk::GetSpriteWidth(VULTRUE_SPRITE)-eggWidth;
	}
	
	//更新鸡蛋的y坐标
	distance=0.5*ACCELERATION*g_time*g_time;
	eggY+=distance;

	agk::SetSpritePosition(EGG_SPRITE,eggX,eggY);//刷新鸡蛋的位置

	g_time++;//时间增加（记住一个鸡蛋掉落结束以及一轮游戏结束后，时间要进行清零）
}


//检测精灵碰撞(篮子和鸡蛋，鸡蛋和地面)
void app::checkCollision()
{
	float eggButtom=agk::GetSpriteY(EGG_SPRITE)+agk::GetSpriteHeight(EGG_SPRITE);//鸡蛋的底部

	if(agk::GetSpriteCollision(BASKET_SPRITE,EGG_SPRITE))//检测篮子和鸡蛋的碰撞
	{
		eggs_Caught++;//接到的鸡蛋数增加

		--g_eggs;//剩余的鸡蛋数减少

		showHitBasket();//显示篮子接到鸡蛋的画面

		resetEgg();//重置鸡蛋到秃鹰的嘴下

		g_time=0;//重置鸡蛋下落时间
	}
	else if(eggButtom >= SCREEN_HEIGHT)//检测鸡蛋和地面的碰撞
	{
		eggs_Missed++;//打碎的鸡蛋数增加

		--g_eggs;//剩余的鸡蛋数减少

		showBrokenEgg();//显示鸡蛋破碎的画面

		resetEgg();//重置鸡蛋到秃鹰的嘴下

		g_time=0;//重置鸡蛋下落时间
	}

}

//显示篮子接到鸡蛋
void app::showHitBasket()
{
	//设置篮子接到鸡蛋的图像的位置
	agk::SetSpritePosition(HIT_BASKET_SPRITE,agk::GetSpriteX(BASKET_SPRITE),agk::GetSpriteY(BASKET_SPRITE));

	//显示
	agk::SetSpriteVisible(HIT_BASKET_SPRITE,1);

	//播放声音
	agk::PlaySound(POP_SOUND);

	agk::Sync();

	agk::Sleep(100);

	agk::SetSpriteVisible(HIT_BASKET_SPRITE,0);
}


//显示鸡蛋破碎，并播放声音
void app::showBrokenEgg()
{
	//设置鸡蛋破碎画面的位置
	agk::SetSpritePosition(BROKEN_EGG_SPRITE,agk::GetSpriteX(EGG_SPRITE),agk::GetSpriteY(EGG_SPRITE)-agk::GetSpriteHeight(EGG_SPRITE)/2);

	//显示
	agk::SetSpriteVisible(BROKEN_EGG_SPRITE,1);

	//播放声音
	agk::PlaySound(BROKEN_SOUND);

	agk::Sync();

	agk::Sleep(100);

	agk::SetSpriteVisible(BROKEN_EGG_SPRITE,0);
}

//重置鸡蛋到秃鹰嘴下
void app::resetEgg()
{
	//一排小蛋减少一个(隐藏当前克隆的小鸡蛋)
	agk::SetSpriteVisible(CLONE_EGG+g_eggs,0);

	//设置鸡蛋的位置
	agk::SetSpriteY(EGG_SPRITE,agk::GetSpriteY(VULTRUE_SPRITE)+agk::GetSpriteHeight(EGG_SPRITE)*1.9);

	agk::Sync();
}


//隐藏游戏界面
void app::hideGame()
{
	//停止播放音乐
	agk::StopMusic();

	//隐藏精灵
	agk::SetSpriteVisible(VULTRUE_SPRITE,0);
	agk::SetSpriteVisible(EGG_SPRITE,0);
	agk::SetSpriteVisible(BASKET_SPRITE,0);
	agk::SetSpriteVisible(FARM_SPRITE,0);
	
	//重置定时器
	agk::ResetTimer();

	//改变游戏状态
	gameState=GAME_OVER;
}


//显示GameOver
void app::showGameOver()
{
	//显示GameOver文本
	agk::SetTextVisible(GAME_OVER_TEXT,1);

	if(!agk::GetSoundsPlaying(COMPLETE_SOUND))
	{
		//播放结束声音
	    agk::PlaySound(COMPLETE_SOUND);
	}

}

//隐藏GameOver
void app::hideGameOver()
{
	agk::SetTextVisible(GAME_OVER_TEXT,0);//隐藏文本

	//停止声音
	agk::StopSound(COMPLETE_SOUND);

	//重置定时器
	agk::ResetTimer();

	//改变游戏状态
	gameState=GAME_SUMMARY;
}

//显示总结画面(接住的鸡蛋数、打碎的鸡蛋数、得分、Results文本、打碎的鸡蛋图片)
void app::displaySummary()
{
	// 游戏总结未完成
	if (g_summaryComplete == 0)
	{
		// 更新接到的鸡蛋数
		agk::SetTextString(EGG_CAUGHT_TEXT, agk::Str(eggs_Caught));
		agk::SetTextX(EGG_CAUGHT_TEXT, agk::GetTextX(CAUGHT_MULTIPLIER_TEXT) + 
			          agk::GetTextTotalWidth(CAUGHT_MULTIPLIER_TEXT) / 2 +
			          agk::GetTextTotalWidth(EGG_CAUGHT_TEXT) / 2);

		// 在文本框内设置鸡蛋的位置
		agk::SetSpritePosition(EGG_SPRITE, agk::GetTextX(CAUGHT_MULTIPLIER_TEXT) - 
			                   agk::GetSpriteWidth(EGG_SPRITE) / 2, 
							   agk::GetTextY(EGG_CAUGHT_TEXT));

		// 更新丢失的鸡蛋数
		agk::SetTextString(EGG_MISSED_TEXT, agk::Str(eggs_Missed));
		agk::SetTextX(EGG_MISSED_TEXT, agk::GetTextX(MISSED_MULTIPLIER_TEXT) + 
					  agk::GetTextTotalWidth(MISSED_MULTIPLIER_TEXT) / 2 +
			          agk::GetTextTotalWidth(EGG_MISSED_TEXT) / 2);

		//在文本框中设置打碎的鸡蛋精灵
		agk::SetSpritePosition(BROKEN_EGG_SPRITE, agk::GetTextX(MISSED_MULTIPLIER_TEXT) - 
			                   agk::GetSpriteWidth(BROKEN_EGG_SPRITE), 
							   agk::GetTextY(EGG_MISSED_TEXT));

		// 显示精灵
		agk::SetSpriteVisible(EGG_SPRITE, 1);
		agk::SetSpriteVisible(BROKEN_EGG_SPRITE, 1);

		// 显示文本
		agk::SetTextVisible(RESULT_TEXT, 1);
		agk::SetTextVisible(EGG_CAUGHT_TEXT, 1);
		agk::SetTextVisible(EGG_MISSED_TEXT, 1);
		agk::SetTextVisible(CAUGHT_MULTIPLIER_TEXT, 1);
		agk::SetTextVisible(MISSED_MULTIPLIER_TEXT, 1);
		agk::SetTextVisible(SCORE_TEXT, 1);

		// 计算总共得分
		for(int i = 0; i <= eggs_Caught; i++)
		{
			// 更新总共得分文本和位置
			agk::SetTextString(SCORE_TEXT, agk::Str(i * SCORE_MULTIPLIER));
			agk::SetTextX(SCORE_TEXT, SCREEN_WIDTH / 2 - 
				          agk::GetTextTotalWidth(SCORE_TEXT) / 2);

			//播放得分声音
			agk::PlaySound(TYPE_SOUND);

			// 延时
			agk::Sleep(100);

			// 刷新屏幕
			agk::Sync();
		}

		// 如果没有鸡蛋打碎
		if (eggs_Caught == MAX_EGGS)
		{
			// 显示完美得分
			agk::SetTextVisible(PERFECT_SCORE_TEXT, 1);
			
			// 播放完美得分声音
			agk::PlaySound(PERFECT_SOUND);

			// 延时
			agk::Sleep(100);

			// 刷新屏幕
			agk::Sync();
		}

		// 计算得分并离开游戏循环之后 
		// 游戏总结完成
		g_summaryComplete = 1;

		// 重置定时器
		agk::ResetTimer();
	}
}

//隐藏总结画面
void app::hideSummary()
{
	// 隐藏文本
	agk::SetTextVisible(GAME_OVER_TEXT, 0);
	agk::SetTextVisible(RESULT_TEXT, 0);
	agk::SetTextVisible(EGG_CAUGHT_TEXT, 0);
	agk::SetTextVisible(EGG_MISSED_TEXT, 0);
	agk::SetTextVisible(CAUGHT_MULTIPLIER_TEXT, 0);
	agk::SetTextVisible(MISSED_MULTIPLIER_TEXT, 0);
	agk::SetTextVisible(SCORE_TEXT, 0);
	agk::SetTextVisible(PERFECT_SCORE_TEXT, 0);


	// 隐藏蛋和打碎的蛋
	agk::SetSpriteVisible(EGG_SPRITE, 0);
	agk::SetSpriteVisible(BROKEN_EGG_SPRITE, 0);

	// 设置秃鹰的起始位置
	float vultureX = SCREEN_WIDTH / 2 - agk::GetSpriteWidth(VULTRUE_SPRITE) / 2;
	float vultureY = 0;
	agk::SetSpritePosition(VULTRUE_SPRITE, vultureX, vultureY);

	//设置篮子的起始位置
	float basketX = SCREEN_WIDTH / 2 - agk::GetSpriteWidth(BASKET_SPRITE) / 2;
	float basketY = SCREEN_HEIGHT - agk::GetSpriteHeight(BASKET_SPRITE);
	agk::SetSpritePosition(BASKET_SPRITE, basketX, basketY);

	// 设置蛋的起始位置
	float eggX = vultureX;
	float eggY = vultureY + agk::GetSpriteHeight(EGG_SPRITE) * 1.5f;
	agk::SetSpritePosition(EGG_SPRITE, eggX, eggY);
	
	// 重置定时器
	agk::ResetTimer();

	// 重置一些全局变量
	g_summaryComplete = 0;
	g_eggs = MAX_EGGS;
	eggs_Missed = 0;
	eggs_Caught = 0;

	// 重置游戏状态
	gameState = GAME_STARTED;
}
