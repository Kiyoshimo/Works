
import random, pygame, sys,time
#导入pygame库
from pygame.locals import *
#导入一些常用的函数和常量
from Variable import * 


screen=pygame.display.set_mode((window_width , window_height))#窗口大小


#BEGIN-----------------加载转换图像-----------------------------
bg = pygame.image.load(bg_image_filename).convert()
f1 = pygame.image.load(f1_image_filename).convert_alpha()
f2 = pygame.image.load(f2_image_filename).convert_alpha()
f3 = pygame.image.load(f3_image_filename).convert_alpha()
f4 = pygame.image.load(f4_image_filename).convert_alpha()
fd1 = pygame.image.load(fd1_image_filename).convert_alpha()
fd2 = pygame.image.load(fd2_image_filename).convert_alpha()
 #END-------------------加载转换图像------------------------


class MFish(pygame.sprite.Sprite):
    def __init__(self):#初始化
        pygame.sprite.Sprite.__init__(self) #完成初始化
        
        self.x=300
        self.y=300
        self.lv=0   #等级
        self.score=0    #分数
        self.image =f2      #调用的图片
        self.rect=pygame.Rect(0,0,65,64)
        
        self.direction=1 #图片方向(1右 -1左）



    def lvup(self):#
        
        if(self.lv==0):
            self.rect=pygame.Rect(self.x,self.y,65,64)
            if(self.direction==-1):
                self.image =f2
            elif(self.direction==1):
                self.image =pygame.transform.flip(f2 , True, False)

        elif(self.lv==1):
            self.rect=pygame.Rect(self.x,self.y,80,60)
            if(self.direction==-1):
                self.image =f3
            elif(self.direction==1):
                self.image =pygame.transform.flip(f3 , True, False)

        elif(self.lv>=2):   
            self.rect=pygame.Rect(self.x,self.y,155,158)
            if(self.direction==-1):
                self.image =f4
            elif(self.direction==1):
                self.image =pygame.transform.flip(f4 , True, False)


        
        
 
    def eat(self):#碰撞判定
        '''
        if(touchfish.lv>self.lv):#他比你高级
            die #死
        if(touchfish.lv==self.lv):#他跟你一样
           #啥事没有
        if(touchfish.lv<self.lv):#他比你小
           self.score=self.score+1
        '''
        self.lv=self.score//3



class EFish(pygame.sprite.Sprite):
    def __init__(self):#完成初始化
        pygame.sprite.Sprite.__init__(self) #完成初始化
        
        self.lv=1  #等级
        self.vx=1   #速度
        self.vy=1
        self.y=-200
        self.x=-200
        self.step=0
        self.image =f1      #调用的图片
        self.rect=pygame.Rect(self.x,self.y,36,31)
        self.direction=1 #图片方向(1右 -1左）

        

   


    def move(self):#随机移动
        
        if(self.step<=0):#随机方向距离
            self.vx=random.randint(-1,1)
            self.vy=random.randint(-1,1)
            self.step=random.randint(1,200)
            self.direction=self.vx
            if(self.vx==0 and self.vy==0):#防止一动不动
                self.step=1
        else:#开始走
            self.x=self.x+self.vx
            self.y=self.y+self.vy
            self.step=self.step-1
            
    def lvup(self):#随机移动
        #BEGIN—————————————图片选择————————————
        if(self.lv==0):
            self.rect=pygame.Rect(self.x,self.y,36,31)
            if(self.direction==-1):
                self.image =f1
            elif(self.direction==1):
                self.image =pygame.transform.flip(f1 , True, False)

        elif(self.lv==1):
            self.rect=pygame.Rect(self.x,self.y,81,69)
            if(self.direction==-1):
                self.image =fd1
            elif(self.direction==1):
                self.image =pygame.transform.flip(fd1 , True, False)

        elif(self.lv==2):   
            self.rect=pygame.Rect(self.x,self.y,160,130)
            if(self.direction==-1):
                self.image =fd2
            elif(self.direction==1):
                self.image =pygame.transform.flip(fd2 , True, False)
         #END—————————————图片选择————————————

    def die(self):#被吃掉或者走出地图外
       
        if(self.x<-160 or self.x>window_width  or self.y> window_height or self.y< -160):
       
            self.vx=random.randint(0,1)
            if(self.vx==0):
                self.direction=self.vx
                
                self.vx=-1
                self.vy=0
                self.step=1

                self.x=window_width-5
                self.y=random.randint(0,window_height)
                
                
            else:
                
                self.vx=1
                self.direction=self.vx
                self.vy=0
                self.step=1
                self.x=-100+5
                self.y=random.randint(0,window_height)
                
            
            self.lv=random.randint(0,2)
 
    def beeat(self):
        self.vx=random.randint(0,1)
        if(self.vx==0):
            self.direction=self.vx
            self.vx=-1
            self.vy=0
            self.step=1

            self.x=window_width-5
            self.y=random.randint(0,window_height)

        else:
                
            self.vx=1
            self.direction=self.vx
            self.vy=0
            self.step=1
            self.x=-100+5
            self.y=random.randint(0,window_height)
                
            
        self.lv=random.randint(0,2)
            
         

