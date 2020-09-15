// Includes, namespace and prototypes
#include "template.h"
using namespace AGK;
app App;

//��Ļ�ֱ��ʲ���
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
//ͼ������
const int TITLE_IMAGE=1;
const int INTRO_IMAGE=2;
const int FARM_IMAGE=3;
const int EGG_IMAGE=4;
const int VULTRUE_IMAGE=5;
const int BASKET_IMAGE=6;
const int BROKEN_EGG_IMAGE=7;
const int HIT_BASKET_IMAGE=8;
//��������
const int TITLE_SPRITE=1;
const int INTRO_SPRITE=2;
const int FARM_SPRITE=3;
const int EGG_SPRITE=4;
const int VULTRUE_SPRITE=5;
const int BASKET_SPRITE=6;
const int BROKEN_EGG_SPRITE=7;
const int HIT_BASKET_SPRITE=8;
//��������
const int INTRO_MUSIC=1;
const int MAIN_MUSIC=2;
//��������
const int POP_SOUND=1;
const int BROKEN_SOUND=2;
const int TYPE_SOUND=3;
const int COMPLETE_SOUND=4;
const int PERFECT_SOUND=5;
//����֡
const int FRAME_WIDTH=120;
const int FRAME_HEIGHT=110;
const int FRAME_COUNT=8;
const int FRAME_PER_SECOND=8;

//�ƶ�����
const float VULTRUE_MOVE=2;
const float BASKET_MOVE=4;

//������ļ��ٶ�
const float ACCELERATION=0.008f;

const int MAX_EGGS=40;//��������
const int CLONE_EGG=100;//����С��������

//�ı�����
const int GAME_OVER_TEXT=1;
const int RESULT_TEXT=2;
const int EGG_CAUGHT_TEXT=3;
const int EGG_MISSED_TEXT=4;
const int SCORE_TEXT=5;
const int CAUGHT_MULTIPLIER_TEXT=6;
const int MISSED_MULTIPLIER_TEXT=7;
const int PERFECT_SCORE_TEXT=8;

//�ı��Ĵ�С
const int TEXT_SIZE=36;

//��Ϸ״̬
const int GAME_STARTED=1;
const int GAME_INTRO=2;
const int GAME_IN_PLAY=3;
const int GAME_OVER=4;
const int GAME_SUMMARY=5;
int gameState=GAME_STARTED;//��Ϸ�ĳ�ʼ״̬


//����ʱ��
const int INTRO_TIME=5;
const int GAME_OVER_TIME=4;
const int GAME_SUMMARY_TIME=5;

//��������
int g_eggs=MAX_EGGS;//ʣ�൰��
int eggs_Missed=0;//����ļ�����
int eggs_Caught=0;//��ס�ļ�����
int g_Score=0;//�ܹ��÷�
int g_time=0;//�����ʱ��
int g_summaryComplete = 0;//��Ϸ�ܽ�
const int SCORE_MULTIPLIER  = 1000;//һ������1000��

void app::Begin( void )
{
	//������Ļ������
	agk::SetWindowTitle("Vulture Trouble");
	agk::SetVirtualResolution(SCREEN_WIDTH,SCREEN_HEIGHT);
	//����ͼ��
	agk::LoadImage(TITLE_IMAGE,"Vulture Trouble/titleScreen.png");
	agk::LoadImage(INTRO_IMAGE,"Vulture Trouble/intro.png");
	agk::LoadImage(FARM_IMAGE,"Vulture Trouble/farm.png");
	agk::LoadImage(EGG_IMAGE,"Vulture Trouble/egg.png");
	agk::LoadImage(VULTRUE_IMAGE,"Vulture Trouble/vulture.png");
	agk::LoadImage(BASKET_IMAGE,"Vulture Trouble/basket.png");
	agk::LoadImage(BROKEN_EGG_IMAGE,"Vulture Trouble/brokenEgg.png");
	agk::LoadImage(HIT_BASKET_IMAGE,"Vulture Trouble/hitBasket.png");
	//��������
	agk::CreateSprite(TITLE_SPRITE,TITLE_IMAGE);
	agk::CreateSprite(INTRO_SPRITE,INTRO_IMAGE);
	agk::CreateSprite(FARM_SPRITE,FARM_IMAGE);
	agk::CreateSprite(EGG_SPRITE,EGG_IMAGE);
	agk::CreateSprite(VULTRUE_SPRITE,VULTRUE_IMAGE);
	agk::CreateSprite(BASKET_SPRITE,BASKET_IMAGE);
	agk::CreateSprite(BROKEN_EGG_SPRITE,BROKEN_EGG_IMAGE);
	agk::CreateSprite(HIT_BASKET_SPRITE,HIT_BASKET_IMAGE);
	//��������
	agk::LoadMusic(INTRO_MUSIC,"Vulture Trouble/vultureLevel.mp3");
	agk::LoadMusic(MAIN_MUSIC,"Vulture Trouble/vultureTrouble.mp3");
	//��������
	agk::LoadSound(POP_SOUND,"Vulture Trouble/pop.wav");
	agk::LoadSound(BROKEN_SOUND,"Vulture Trouble/clap.wav");
	agk::LoadSound(TYPE_SOUND,"Vulture Trouble/type.wav");
	agk::LoadSound(COMPLETE_SOUND,"Vulture Trouble/complete.wav");
	agk::LoadSound(PERFECT_SOUND,"Vulture Trouble/vulturePerfect.wav");
	//���ö���֡
	agk::SetSpriteAnimation(VULTRUE_SPRITE,FRAME_WIDTH,FRAME_HEIGHT,FRAME_COUNT);

	//���þ���λ��,ͺӥλ����Ļ�������ġ�����λ����Ļ�ײ����ġ�����λ��ͺӥ�첿
	float vultrueX=SCREEN_WIDTH/2-agk::GetSpriteWidth(VULTRUE_SPRITE)/2;
	float vultrueY=0;
	agk::SetSpritePosition(VULTRUE_SPRITE,vultrueX,vultrueY);

	float basketX=SCREEN_WIDTH/2-agk::GetSpriteWidth(BASKET_SPRITE)/2;
	float basketY=SCREEN_HEIGHT-agk::GetSpriteHeight(BASKET_SPRITE);
	agk::SetSpritePosition(BASKET_SPRITE,basketX,basketY);

	float eggX=vultrueX;
	float eggY=vultrueY+agk::GetSpriteHeight(EGG_SPRITE)*1.9;
	agk::SetSpritePosition(EGG_SPRITE,eggX,eggY);

	//���ؾ���
	agk::SetSpriteVisible(TITLE_SPRITE,0);
	agk::SetSpriteVisible(INTRO_SPRITE,0);
	agk::SetSpriteVisible(FARM_SPRITE,0);
	agk::SetSpriteVisible(EGG_SPRITE,0);
	agk::SetSpriteVisible(VULTRUE_SPRITE,0);
	agk::SetSpriteVisible(BASKET_SPRITE,0);
	agk::SetSpriteVisible(BROKEN_EGG_SPRITE,0);
	agk::SetSpriteVisible(HIT_BASKET_SPRITE,0);


	//����Ļ��������һ��С��,��ʾ��Ϸʣ��ĵ���(40)
	for(int i=0;i<MAX_EGGS;i++)
	{
		int clone=CLONE_EGG+i;//�µ�������
		float scale=0.5;
		agk::CloneSprite(clone,EGG_SPRITE);//��¡
		agk::SetSpriteScale(clone,scale,scale);//��С��
		//����С����λ��
		float x=agk::GetSpriteWidth(clone)*i;
		float y=0.0f;
		agk::SetSpritePosition(clone,x,y);
	}

	//�����ı�
	agk::CreateText(GAME_OVER_TEXT,"GAME OVER");
	agk::CreateText(RESULT_TEXT,"GAME RESULTS");
	agk::CreateText(EGG_CAUGHT_TEXT,agk::Str(eggs_Caught));
	agk::CreateText(EGG_MISSED_TEXT,agk::Str(eggs_Missed));
	agk::CreateText(CAUGHT_MULTIPLIER_TEXT," X ");
	agk::CreateText(MISSED_MULTIPLIER_TEXT," X ");
	agk::CreateText(SCORE_TEXT,agk::Str(g_Score));
	agk::CreateText(PERFECT_SCORE_TEXT,"PERFECT SCORE!");


	//�����ı��Ĵ�С
	agk::SetTextSize(GAME_OVER_TEXT,TEXT_SIZE);
	agk::SetTextSize(EGG_CAUGHT_TEXT,TEXT_SIZE);
	agk::SetTextSize(EGG_MISSED_TEXT,TEXT_SIZE);
	agk::SetTextSize(SCORE_TEXT,TEXT_SIZE);
	agk::SetTextSize(RESULT_TEXT,TEXT_SIZE);
	agk::SetTextSize(CAUGHT_MULTIPLIER_TEXT,TEXT_SIZE);
	agk::SetTextSize(MISSED_MULTIPLIER_TEXT,TEXT_SIZE);
	agk::SetTextSize(PERFECT_SCORE_TEXT,TEXT_SIZE);


	//�����ı���λ��
	float gameOverX=SCREEN_WIDTH/2-agk::GetTextTotalWidth(GAME_OVER_TEXT)/2;//game over
	float gameOverY=SCREEN_HEIGHT/2-agk::GetTextTotalHeight(GAME_OVER_TEXT)/2;
	agk::SetTextPosition(GAME_OVER_TEXT,gameOverX,gameOverY);

	float resultX=SCREEN_WIDTH/2-agk::GetTextTotalWidth(RESULT_TEXT)/2;  //game result
	float resultY=SCREEN_HEIGHT/6-agk::GetTextTotalHeight(RESULT_TEXT)/2;
	agk::SetTextPosition(RESULT_TEXT,resultX,resultY);

	float eggCaughtX=SCREEN_WIDTH/4-agk::GetTextTotalWidth(EGG_CAUGHT_TEXT)/2; //��ס�ļ���
	float eggCaughtY=SCREEN_HEIGHT/2-agk::GetTextTotalHeight(EGG_CAUGHT_TEXT)/2;
	agk::SetTextPosition(EGG_CAUGHT_TEXT,eggCaughtX,eggCaughtY);

	float eggMissedX=SCREEN_WIDTH-SCREEN_WIDTH/4;
	float eggMissedY=SCREEN_HEIGHT/2-agk::GetTextTotalHeight(EGG_MISSED_TEXT)/2;//����ļ���
	agk::SetTextPosition(EGG_MISSED_TEXT,eggMissedX,eggMissedY);

	float scoreX=SCREEN_WIDTH/2-agk::GetTextTotalWidth(SCORE_TEXT)/2;//�ܹ��÷�
	float scoreY=SCREEN_HEIGHT-agk::GetTextTotalHeight(SCORE_TEXT)*4;
	agk::SetTextPosition(SCORE_TEXT,scoreX,scoreY);

	//�����÷�
	float perfectScoreTextX = SCREEN_WIDTH / 2 - agk::GetTextTotalWidth(PERFECT_SCORE_TEXT) / 2;
	float perfectScoreTextY = SCREEN_HEIGHT - agk::GetTextTotalHeight(SCORE_TEXT) * 2;
	agk::SetTextPosition(PERFECT_SCORE_TEXT, perfectScoreTextX, perfectScoreTextY);

	//��ס�����Ķ����ı�
	float caughtMultiplierTextX = SCREEN_WIDTH / 4;
	float caughtMultiplierTextY = SCREEN_HEIGHT / 2 - agk::GetTextTotalHeight(CAUGHT_MULTIPLIER_TEXT) / 2;
	agk::SetTextPosition(CAUGHT_MULTIPLIER_TEXT, caughtMultiplierTextX, caughtMultiplierTextY);

	//��ʧ�����Ķ����ı�
	float missedMultiplierTextX = SCREEN_WIDTH - SCREEN_WIDTH / 3;
	float missedMultiplierTextY = SCREEN_HEIGHT / 2 - agk::GetTextTotalHeight(MISSED_MULTIPLIER_TEXT) / 2;
	agk::SetTextPosition(MISSED_MULTIPLIER_TEXT, missedMultiplierTextX, missedMultiplierTextY);

	//�����ı�
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
		//��ʾ�������
		displayTitle();

		//�Ƿ���Enter��
		if(agk::GetRawKeyPressed(AGK_KEY_ENTER))
		{
			hideTitle();
		}
		break;

	case GAME_INTRO:
		displayIntro();//��ʾ���ܽ���
		if(agk::Timer() >= INTRO_TIME)
		{
			hideIntro();//����
		}
		break;

	case GAME_IN_PLAY:
		playGame();//����Ϸ
		if(g_eggs <= 0)//�ж�ʣ�൰���Ƿ�Ϊ0 
		{
			hideGame();//������Ϸ
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

	//ˢ����Ļ
	agk::Sync();
}


void app::End( void )
{

}

//��ʾ�������
void app::displayTitle()
{
	if(!agk::GetSpriteVisible(TITLE_SPRITE))//���������治���ӣ�����
	{
		agk::SetSpriteVisible(TITLE_SPRITE,1);
	}

	if(!agk::GetMusicPlaying())//���û�в������֣���ѭ����������
	{
		agk::PlayMusic(INTRO_MUSIC,1,INTRO_MUSIC,INTRO_MUSIC);
	}
}

//���ر������
void app::hideTitle()
{
	agk::SetSpriteVisible(TITLE_SPRITE,0);
	agk::ResetTimer();//���ö�ʱ��
	gameState=GAME_INTRO;//�ı���Ϸ״̬
}

//��ʾ���ܽ���
void app::displayIntro()
{
	if(!agk::GetSpriteVisible(INTRO_SPRITE))
	{
		agk::SetSpriteVisible(INTRO_SPRITE,1);//���ܽ�����ӻ�
	}

	if(agk::GetMusicPlaying() != MAIN_MUSIC)
	{
		agk::PlayMusic(MAIN_MUSIC,1,MAIN_MUSIC,MAIN_MUSIC);//ѭ������������
	}
}


//���ؽ��ܽ���
void app::hideIntro()
{
	agk::SetSpriteVisible(INTRO_SPRITE,0);//���ؽ��ܽ���

	agk::SetSpriteVisible(FARM_SPRITE,1);
	agk::SetSpriteVisible(VULTRUE_SPRITE,1);
	agk::SetSpriteVisible(BASKET_SPRITE,1);
	agk::SetSpriteVisible(EGG_SPRITE,1);

	//��ʾһ��С��
	for(int i=0;i<MAX_EGGS;i++)
	{
		int clone=CLONE_EGG+i;
		agk::SetSpriteVisible(clone,1);
	}

	gameState=GAME_IN_PLAY;//�ı���Ϸ״̬
}

//��ʼ����Ϸ
void app::playGame()
{	
	basketMove();//�������ӵ�λ��
	vultrueMove();//����ͺӥ��λ��
	eggMove();//���¼�����λ��
	checkCollision();//��⾫����ײ
}



//ͺӥ����Ļ�����Ϸ������ƶ�
void app::vultrueMove()
{
	//���Ŷ���֡
	if(!agk::GetSpritePlaying(VULTRUE_SPRITE))
	{
		agk::PlaySprite(VULTRUE_SPRITE,FRAME_PER_SECOND);
	}

	float vultrueX=agk::GetSpriteX(VULTRUE_SPRITE);//��ȡ��ǰͺӥ��xλ��
	float vultrueWidth=agk::GetSpriteWidth(VULTRUE_SPRITE);//��ȡͺӥ�Ŀ��

	if(vultrueX <= 0)//���������
	{
		agk::SetSpriteFlip(VULTRUE_SPRITE,0,1);//��ֱ�����Ϸ�תͺӥ
		agk::SetSpriteAngle(VULTRUE_SPRITE,180.0f);//������ת180��
	}
	if(vultrueX >= SCREEN_WIDTH-vultrueWidth)//�������ұ�
	{
		agk::SetSpriteFlip(VULTRUE_SPRITE,0,0);
		agk::SetSpriteAngle(VULTRUE_SPRITE,0.0f);//����ԭ����0��
	}                                                          

	if(agk::GetSpriteAngle(VULTRUE_SPRITE) == 180.0f)//����
	{
		vultrueX+=VULTRUE_MOVE;
	}
	else//����
	{
		vultrueX-=VULTRUE_MOVE;
	}

	agk::SetSpriteX(VULTRUE_SPRITE,vultrueX);//����ͺӥ��xλ��
}


//�û�ͨ�����Ұ��� �ƶ����ӵ�λ�ã�xλ�ã�
void app::basketMove()
{
	float basketX=agk::GetSpriteX(BASKET_SPRITE);
	float basketWidth=agk::GetSpriteWidth(BASKET_SPRITE);//���ӵĿ��

	if(agk::GetRawKeyState(AGK_KEY_LEFT))//�Ƿ����������
	{
		if(basketX <= 0)//�Ƿ�ﵽ��߽�
		{
			basketX=0;
		}
		else
		{
			basketX-=BASKET_MOVE;
		}
	}

	if(agk::GetRawKeyState(AGK_KEY_RIGHT))//�Ƿ����Ҽ�����
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

	agk::SetSpriteX(BASKET_SPRITE,basketX);//ˢ�����ӵ�xλ��
}


//���¼�����λ��
void app::eggMove()
{
	float eggX=agk::GetSpriteX(VULTRUE_SPRITE);//������xλ����ͺӥλ���й�
	float eggY=agk::GetSpriteY(EGG_SPRITE);
	float eggWidth=agk::GetSpriteWidth(EGG_SPRITE);
	float distance;

	//�����ĳ�ʼλ��λ��ͺӥ���������
	if(agk::GetSpriteAngle(VULTRUE_SPRITE) == 180.0f)//ͺӥ����ʱ
	{
		eggX=agk::GetSpriteX(VULTRUE_SPRITE)+agk::GetSpriteWidth(VULTRUE_SPRITE)-eggWidth;
	}
	
	//���¼�����y����
	distance=0.5*ACCELERATION*g_time*g_time;
	eggY+=distance;

	agk::SetSpritePosition(EGG_SPRITE,eggX,eggY);//ˢ�¼�����λ��

	g_time++;//ʱ�����ӣ���סһ��������������Լ�һ����Ϸ������ʱ��Ҫ�������㣩
}


//��⾫����ײ(���Ӻͼ����������͵���)
void app::checkCollision()
{
	float eggButtom=agk::GetSpriteY(EGG_SPRITE)+agk::GetSpriteHeight(EGG_SPRITE);//�����ĵײ�

	if(agk::GetSpriteCollision(BASKET_SPRITE,EGG_SPRITE))//������Ӻͼ�������ײ
	{
		eggs_Caught++;//�ӵ��ļ���������

		--g_eggs;//ʣ��ļ���������

		showHitBasket();//��ʾ���ӽӵ������Ļ���

		resetEgg();//���ü�����ͺӥ������

		g_time=0;//���ü�������ʱ��
	}
	else if(eggButtom >= SCREEN_HEIGHT)//��⼦���͵������ײ
	{
		eggs_Missed++;//����ļ���������

		--g_eggs;//ʣ��ļ���������

		showBrokenEgg();//��ʾ��������Ļ���

		resetEgg();//���ü�����ͺӥ������

		g_time=0;//���ü�������ʱ��
	}

}

//��ʾ���ӽӵ�����
void app::showHitBasket()
{
	//�������ӽӵ�������ͼ���λ��
	agk::SetSpritePosition(HIT_BASKET_SPRITE,agk::GetSpriteX(BASKET_SPRITE),agk::GetSpriteY(BASKET_SPRITE));

	//��ʾ
	agk::SetSpriteVisible(HIT_BASKET_SPRITE,1);

	//��������
	agk::PlaySound(POP_SOUND);

	agk::Sync();

	agk::Sleep(100);

	agk::SetSpriteVisible(HIT_BASKET_SPRITE,0);
}


//��ʾ�������飬����������
void app::showBrokenEgg()
{
	//���ü������黭���λ��
	agk::SetSpritePosition(BROKEN_EGG_SPRITE,agk::GetSpriteX(EGG_SPRITE),agk::GetSpriteY(EGG_SPRITE)-agk::GetSpriteHeight(EGG_SPRITE)/2);

	//��ʾ
	agk::SetSpriteVisible(BROKEN_EGG_SPRITE,1);

	//��������
	agk::PlaySound(BROKEN_SOUND);

	agk::Sync();

	agk::Sleep(100);

	agk::SetSpriteVisible(BROKEN_EGG_SPRITE,0);
}

//���ü�����ͺӥ����
void app::resetEgg()
{
	//һ��С������һ��(���ص�ǰ��¡��С����)
	agk::SetSpriteVisible(CLONE_EGG+g_eggs,0);

	//���ü�����λ��
	agk::SetSpriteY(EGG_SPRITE,agk::GetSpriteY(VULTRUE_SPRITE)+agk::GetSpriteHeight(EGG_SPRITE)*1.9);

	agk::Sync();
}


//������Ϸ����
void app::hideGame()
{
	//ֹͣ��������
	agk::StopMusic();

	//���ؾ���
	agk::SetSpriteVisible(VULTRUE_SPRITE,0);
	agk::SetSpriteVisible(EGG_SPRITE,0);
	agk::SetSpriteVisible(BASKET_SPRITE,0);
	agk::SetSpriteVisible(FARM_SPRITE,0);
	
	//���ö�ʱ��
	agk::ResetTimer();

	//�ı���Ϸ״̬
	gameState=GAME_OVER;
}


//��ʾGameOver
void app::showGameOver()
{
	//��ʾGameOver�ı�
	agk::SetTextVisible(GAME_OVER_TEXT,1);

	if(!agk::GetSoundsPlaying(COMPLETE_SOUND))
	{
		//���Ž�������
	    agk::PlaySound(COMPLETE_SOUND);
	}

}

//����GameOver
void app::hideGameOver()
{
	agk::SetTextVisible(GAME_OVER_TEXT,0);//�����ı�

	//ֹͣ����
	agk::StopSound(COMPLETE_SOUND);

	//���ö�ʱ��
	agk::ResetTimer();

	//�ı���Ϸ״̬
	gameState=GAME_SUMMARY;
}

//��ʾ�ܽử��(��ס�ļ�����������ļ��������÷֡�Results�ı�������ļ���ͼƬ)
void app::displaySummary()
{
	// ��Ϸ�ܽ�δ���
	if (g_summaryComplete == 0)
	{
		// ���½ӵ��ļ�����
		agk::SetTextString(EGG_CAUGHT_TEXT, agk::Str(eggs_Caught));
		agk::SetTextX(EGG_CAUGHT_TEXT, agk::GetTextX(CAUGHT_MULTIPLIER_TEXT) + 
			          agk::GetTextTotalWidth(CAUGHT_MULTIPLIER_TEXT) / 2 +
			          agk::GetTextTotalWidth(EGG_CAUGHT_TEXT) / 2);

		// ���ı��������ü�����λ��
		agk::SetSpritePosition(EGG_SPRITE, agk::GetTextX(CAUGHT_MULTIPLIER_TEXT) - 
			                   agk::GetSpriteWidth(EGG_SPRITE) / 2, 
							   agk::GetTextY(EGG_CAUGHT_TEXT));

		// ���¶�ʧ�ļ�����
		agk::SetTextString(EGG_MISSED_TEXT, agk::Str(eggs_Missed));
		agk::SetTextX(EGG_MISSED_TEXT, agk::GetTextX(MISSED_MULTIPLIER_TEXT) + 
					  agk::GetTextTotalWidth(MISSED_MULTIPLIER_TEXT) / 2 +
			          agk::GetTextTotalWidth(EGG_MISSED_TEXT) / 2);

		//���ı��������ô���ļ�������
		agk::SetSpritePosition(BROKEN_EGG_SPRITE, agk::GetTextX(MISSED_MULTIPLIER_TEXT) - 
			                   agk::GetSpriteWidth(BROKEN_EGG_SPRITE), 
							   agk::GetTextY(EGG_MISSED_TEXT));

		// ��ʾ����
		agk::SetSpriteVisible(EGG_SPRITE, 1);
		agk::SetSpriteVisible(BROKEN_EGG_SPRITE, 1);

		// ��ʾ�ı�
		agk::SetTextVisible(RESULT_TEXT, 1);
		agk::SetTextVisible(EGG_CAUGHT_TEXT, 1);
		agk::SetTextVisible(EGG_MISSED_TEXT, 1);
		agk::SetTextVisible(CAUGHT_MULTIPLIER_TEXT, 1);
		agk::SetTextVisible(MISSED_MULTIPLIER_TEXT, 1);
		agk::SetTextVisible(SCORE_TEXT, 1);

		// �����ܹ��÷�
		for(int i = 0; i <= eggs_Caught; i++)
		{
			// �����ܹ��÷��ı���λ��
			agk::SetTextString(SCORE_TEXT, agk::Str(i * SCORE_MULTIPLIER));
			agk::SetTextX(SCORE_TEXT, SCREEN_WIDTH / 2 - 
				          agk::GetTextTotalWidth(SCORE_TEXT) / 2);

			//���ŵ÷�����
			agk::PlaySound(TYPE_SOUND);

			// ��ʱ
			agk::Sleep(100);

			// ˢ����Ļ
			agk::Sync();
		}

		// ���û�м�������
		if (eggs_Caught == MAX_EGGS)
		{
			// ��ʾ�����÷�
			agk::SetTextVisible(PERFECT_SCORE_TEXT, 1);
			
			// ���������÷�����
			agk::PlaySound(PERFECT_SOUND);

			// ��ʱ
			agk::Sleep(100);

			// ˢ����Ļ
			agk::Sync();
		}

		// ����÷ֲ��뿪��Ϸѭ��֮�� 
		// ��Ϸ�ܽ����
		g_summaryComplete = 1;

		// ���ö�ʱ��
		agk::ResetTimer();
	}
}

//�����ܽử��
void app::hideSummary()
{
	// �����ı�
	agk::SetTextVisible(GAME_OVER_TEXT, 0);
	agk::SetTextVisible(RESULT_TEXT, 0);
	agk::SetTextVisible(EGG_CAUGHT_TEXT, 0);
	agk::SetTextVisible(EGG_MISSED_TEXT, 0);
	agk::SetTextVisible(CAUGHT_MULTIPLIER_TEXT, 0);
	agk::SetTextVisible(MISSED_MULTIPLIER_TEXT, 0);
	agk::SetTextVisible(SCORE_TEXT, 0);
	agk::SetTextVisible(PERFECT_SCORE_TEXT, 0);


	// ���ص��ʹ���ĵ�
	agk::SetSpriteVisible(EGG_SPRITE, 0);
	agk::SetSpriteVisible(BROKEN_EGG_SPRITE, 0);

	// ����ͺӥ����ʼλ��
	float vultureX = SCREEN_WIDTH / 2 - agk::GetSpriteWidth(VULTRUE_SPRITE) / 2;
	float vultureY = 0;
	agk::SetSpritePosition(VULTRUE_SPRITE, vultureX, vultureY);

	//�������ӵ���ʼλ��
	float basketX = SCREEN_WIDTH / 2 - agk::GetSpriteWidth(BASKET_SPRITE) / 2;
	float basketY = SCREEN_HEIGHT - agk::GetSpriteHeight(BASKET_SPRITE);
	agk::SetSpritePosition(BASKET_SPRITE, basketX, basketY);

	// ���õ�����ʼλ��
	float eggX = vultureX;
	float eggY = vultureY + agk::GetSpriteHeight(EGG_SPRITE) * 1.5f;
	agk::SetSpritePosition(EGG_SPRITE, eggX, eggY);
	
	// ���ö�ʱ��
	agk::ResetTimer();

	// ����һЩȫ�ֱ���
	g_summaryComplete = 0;
	g_eggs = MAX_EGGS;
	eggs_Missed = 0;
	eggs_Caught = 0;

	// ������Ϸ״̬
	gameState = GAME_STARTED;
}
