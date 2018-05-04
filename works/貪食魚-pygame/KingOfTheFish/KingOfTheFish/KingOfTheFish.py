import random, pygame, sys,time
#导入pygame库
from pygame.locals import *
#导入一些常用的函数和常量
from Variable import * 
#导入参数文件
from Class import * 

from sys import exit
#向sys模块借一个exit函数用来退出程序
 
pygame.init()
#初始化pygame,为使用硬件做准备
 

pygame.display.set_caption("King of The Fish!")#窗口名字
#设置窗口标题

fclock = pygame.time.Clock()#fps控制



#BEGIN-----------------音乐部分--------------------------------
try: # 尝试放音乐
    pygame.mixer.init()  # 音乐初始化
except: # 如果音乐无法播放
    AudioDevice=0
    print("no earphone")
def music():
    global AudioDevice,mh0,mh1
    if(AudioDevice==1):
        if(mh0==0 and mh1==1):
            pygame.mixer.music.load(go_music_filename)
            pygame.mixer.music.play(-1,0.0)
        if(mh0==1 and mh1==0):
            pygame.mixer.music.stop()
        mh0=mh1
#END-----------------音乐部分---------------------------


def show_text(text, x, y): 
    x = x
    y = y
    text = font.render(text, True, (255, 255, 255))
    screen.blit(text, (x, y))
    pygame.display.update()

 
    
MyFish = MFish( )
EF1=EFish()
EF2=EFish()
EF3=EFish()
EF4=EFish()
EF5=EFish()
EF6=EFish()
EF7=EFish()
EF8=EFish()
EF9=EFish()



moveX,moveY = 0,0
gameLoop = True


group = pygame.sprite.Group()

group.add(MyFish,EF1,EF2,EF3,EF4,EF5,EF6,EF7,EF8,EF9)
EF=[EF1,EF2,EF3,EF4,EF5,EF6,EF7,EF8,EF9]
font = pygame.font.Font("msyh.ttc", 24)  

while gameLoop:
    if(b==0):
        screen.blit(bg,(0,0) )    #背景
        show_text("1104105355黄佳禾           按k键开始", 0,0)
       
        
        for event in pygame.event.get():
            if (event.type == pygame.KEYDOWN):
                if(event.key == pygame.K_k):
                    b=1

        pygame.display.flip()  
    if(b==1):
        ticks = pygame.time.get_ticks()#计时器

        for event in pygame.event.get():
            if (event.type == pygame.QUIT):
                gameLoop = False
            #BEGIN-----------------控制处理-----------------------------            
            if (event.type == pygame.KEYDOWN):
                if (event.key == pygame.K_a):
                    MoveLeft =1
                if (event.key == pygame.K_d):
                    MoveRight =1
                if (event.key == pygame.K_w):
                    MoveUp =1
                if (event.key == pygame.K_s):
                    MoveDown =1 
                if (event.key == pygame.K_UP):#作弊
                    MyFish.score=MyFish.score+1
            if (event.type == pygame.KEYUP):
                if (event.key == pygame.K_a):
                    MoveLeft =0
                if (event.key == pygame.K_d):
                    MoveRight =0
                if (event.key == pygame.K_w):
                    MoveUp =0
                if (event.key == pygame.K_s):
                    MoveDown =0
                
            if(MoveLeft ==0):
                if(MoveRight ==1):
                    moveX=1
                if(MoveRight ==0):
                    moveX=0
            if(MoveLeft ==1):
                if(MoveRight ==1):
                    moveX=0
                else:
                    moveX=-1
                
            if(MoveUp ==0):
                if(MoveDown ==1):
                    moveY=1
                if(MoveDown ==0):
                    moveY=0
            if(MoveUp ==1):
                if(MoveDown ==1):
                    moveY=0
                else:
                    moveY=-1
        #END-----------------控制处理-----------------------------         
    
        
                
    
        MyFish.direction=moveX 
        MyFish.x += moveX 
        MyFish.y  += moveY 
    
  
        mh1=1   #声音
        music()#声音
    
        EF1.move()
        EF2.move()
        EF3.move()
        EF4.move()
        EF5.move()
        EF6.move()
        EF7.move()
        EF8.move()
        EF9.move()

        MyFish.lvup()
        MyFish.eat()

        EF1.lvup()
        EF2.lvup()
        EF3.lvup()
        EF4.lvup()
        EF5.lvup()
        EF6.lvup()
        EF7.lvup()
        EF8.lvup()
        EF9.lvup()






        EF1.die()
        EF2.die()
        EF3.die()
        EF4.die()
        EF5.die()
        EF6.die()
        EF7.die()
        EF8.die()
        EF9.die()
    
   

    
    
        group.update()
  


        #list_collide    =  pygame.sprite.spritecollide(MyFish, EF, False)
        #print( list_collide )
        #绝望了-----------------------------------------------
    
        for i in range(9):
            t=pygame.sprite.collide_rect(MyFish,EF[i])
            if(t==1):
                if(EF[i].lv<=MyFish.lv):
                    EF[i].beeat()
                    MyFish.score=MyFish.score+1
                else:
                    exit()
      
    

        screen.blit(bg,(0,0) )    #背景
        
        group.draw(screen)
        show_text("分数："+str(MyFish.score), 0,0)
        pygame.display.flip() 
        fclock.tick(FPS)
 



pygame.quit()

