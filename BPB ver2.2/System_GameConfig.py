import os

Config_FileName = "config.ini"
class System_GameConfig:
    CurrentName = "NoName"
    def __init__(self):
        
        if (os.path.exists(Config_FileName)):
            if (os.path.isfile(Config_FileName)):
                #Load File here
                print("Load File")
                f = open(Config_FileName, 'r')

                for line in f:
                    token, data = line.split("=")
                    data = data.replace("\n", "")
                    if (token == "Name "):
                        self.CurrentName = data
                        print("Loaded Name %s" % data)

                f.close()
            else:
                raise(IOError('請把config.ini 資料夾刪除.'))
        else:
            #We are making a new one
            print("Create File")
            f = open(Config_FileName, 'w')
            f.write("Name =NoName\n")
            f.close()
            
    def write(self):
        f = open(Config_FileName, 'w')
        f.write("Name =%s" % self.CurrentName)
        f.close()
