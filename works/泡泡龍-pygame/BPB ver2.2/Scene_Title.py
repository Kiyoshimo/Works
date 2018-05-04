import pygame
from sys import exit

from pygame_button import *
from Scene_Changer import *
from Netplay import *
from threading import *
from DB import DB
import time
class Scene_Title:
    mfont = pygame.font.SysFont("Arial Black", 24, True, True)
    graphics_bg = pygame.image.load("Graphics/bg0001.png")

    audio_bgm_filename = "Audio/BGM/select.ogg"

    audio_se_ok_filename = "Audio/SE/button_p.wav"
    frame = 0

    WINDOWWIDTH = 435 # size of window's width in pixels
    WINDOWHEIGHT = 720 # size of windows' height in pixels
    
    def __init__(self):
        
        ####改解析度
        self.NewScreen = pygame.display.set_mode((self.WINDOWWIDTH,self.WINDOWHEIGHT), 0, 32)

        try:
            self.audio_se_ok = pygame.mixer.Sound(self.audio_se_ok_filename)
            pygame.mixer.music.load(self.audio_bgm_filename)

            pygame.mixer.music.play(-1)
        except:
            print("Mixer Init Failed!")

        self.button1_image = self.mfont.render("COM PLAY", 12, (192,0,0))
        self.button1_image_b = self.mfont.render("COM PLAY", 12, (127,127,127))
        self.button2_image = self.mfont.render("ONLINE PLAY", 12, (192,0,0))
        self.button2_image_b = self.mfont.render("ONLINE PLAY", 12, (127,127,127))
        self.button3_image = self.mfont.render("OPTION", 12, (192,0,0))
        self.button3_image_b = self.mfont.render("OPTION", 12, (127,127,127))
        self.button4_image = self.mfont.render("EXIT", 12, (192,0,0))
        self.button4_image_b = self.mfont.render("EXIT", 12, (127,127,127))
        self.button5_image = self.mfont.render("SCOREBOARD", 12, (192,0,0))
        self.button5_image_b = self.mfont.render("SCOREBOARD", 12, (127,127,127))
        
        self.button1 = pyButton();
        self.button1.setImage(self.button1_image, True)
        self.button2 = pyButton();
        self.button2.setImage(self.button2_image, True)
        self.button3 = pyButton();
        self.button3.setImage(self.button3_image, True)
        self.button4 = pyButton();
        self.button4.setImage(self.button4_image, True)
        
        self.button5 = pyButton();
        self.button5.setImage(self.button5_image_b, True)
        
        self.button1.rect.y = 420
        self.button2.rect.y = 460
        self.button3.rect.y = 540
        self.button4.rect.y = 580
        self.button5.rect.y = 500
        
        self.ButtonGroup = pygame.sprite.Group()
        self.ButtonGroup.add([self.button1, self.button2, self.button3, self.button4, self.button5])
        self.netplay = None

        DB()
    def update(self, screen):
        global Scene

        mouse1, mouse2 ,mouse3 = (False,False,False)
        
        # 退出事件處理
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            elif event.type == MOUSEMOTION:
                cur_x, cur_y = event.pos
            elif event.type == MOUSEBUTTONDOWN:
                if event.button == 1:
                    mouse1 = True
        
        cur_x, cur_y = pygame.mouse.get_pos()
        
        self.frame += 1
        screen.blit(self.graphics_bg, (0,0))
        self.ButtonGroup.draw(screen)

        if (self.button1.rect.collidepoint(cur_x,cur_y)):
            if (self.frame % 10 > 5):
                self.button1.setImage(self.button1_image)
            else:
                self.button1.setImage(self.button1_image_b)

            if (mouse1):
                if (pygame.mixer.get_init()):
                    self.audio_se_ok.play()

                from Scene_GamePlay_Double import Scene_GamePlay_Double
                return Scene_Changer(Scene_GamePlay_Double(), screen)
        else:
            self.button1.setImage(self.button1_image)
            
        if (self.button2.rect.collidepoint(cur_x,cur_y)):
            if (self.frame % 10 > 5):
                self.button2.setImage(self.button2_image)
            else:
                self.button2.setImage(self.button2_image_b)

            if (mouse1):
                if (pygame.mixer.get_init()):
                    self.audio_se_ok.play()

                #Uthread = Thread(target = Netplay.show, args = ())
                #Uthread.start()
                self.netplay = Netplay()
                self.netplay.show()
                print(self.netplay.Target_IP)
                print(self.netplay.TCP_Connected)
                if (self.netplay.TCP_Connected == True):
                    from Scene_GamePlay_Double import Scene_GamePlay_Double
                    return Scene_Changer(Scene_GamePlay_Double(self.netplay), screen)
        else:
            self.button2.setImage(self.button2_image)

        if (self.button3.rect.collidepoint(cur_x,cur_y)):
            if (self.frame % 10 > 5):
                self.button3.setImage(self.button3_image)
            else:
                self.button3.setImage(self.button3_image_b)

            if (mouse1):
                if (pygame.mixer.get_init()):
                    self.audio_se_ok.play()
                from Scene_Option import Scene_Option
                return Scene_Changer(Scene_Option(), screen)
        else:
            self.button3.setImage(self.button3_image)

        if (self.button4.rect.collidepoint(cur_x,cur_y)):
            if (self.frame % 10 > 5):
                self.button4.setImage(self.button4_image)
            else:
                self.button4.setImage(self.button4_image_b)

            if (mouse1):
                pygame.quit()
                quit()
        else:
            self.button4.setImage(self.button4_image)
            
        if (self.button5.rect.collidepoint(cur_x,cur_y)):
            if (self.frame % 10 > 5):
                self.button5.setImage(self.button5_image)
            else:
                self.button5.setImage(self.button5_image_b)
            if (mouse1 == True):
                if (pygame.mixer.get_init()):
                    self.audio_se_ok.play()

                from Scene_ScoreBoard import Scene_ScoreBoard
                return Scene_Changer(Scene_ScoreBoard(), screen)
        else:
            self.button5.setImage(self.button5_image)
