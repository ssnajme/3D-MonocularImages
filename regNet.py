import torch
import torch.nn as nn


class ConvBlock(nn.Module):
    def __init__(self, in_channels, out_channels, stride=1, expand_ratio=1):
        super(ConvBlock, self).__init__()
        # add comment for this line
        hidden_channels = round(in_channels * expand_ratio)
        self.conv = nn.Sequential(
            nn.Conv2d(in_channels, hidden_channels, kernel_size=3, bias=False),
            nn.BatchNorm2d(hidden_channels),
            nn.ReLU(inplace=True),
            nn.Conv2d(
                hidden_channels,
                hidden_channels,
                kernel_size=3,
                stride=stride,
                bias=False,
            ),
            nn.BatchNorm2d(hidden_channels),
            nn.ReLU(inplace=True),
            nn.Conv2d(hidden_channels, out_channels, kernel_size=1, bias=False),
            nn.BatchNorm2d(out_channels),
        )

    def forward(self, x):
        return self.conv(x) + x


class RegNet(nn.Module):
    def __init__(self, num_classes=1000):
        super(RegNet, self).__init__()
        self.stem = nn.Sequential(
            nn.Conv2d(3, 32, kernel_size=3, stride=2, padding=1, bias=False),
            nn.BatchNorm2d(32),
            nn.ReLU(inplace=True),
        )

        # this need a better comment
        self.layers = nn.ModuleList([
                # this is for Block: Num_blocks, Input channels, Output channels
                self.make_stage(32, 64, 4, 1),
                self.make_stage(64, 128, 4, 1),
                self.make_stage(128, 256, 4, 2),
            ])
        
        self.fc = nn.Linear(256, num_classes)

    # explain this part in comment 
    def make_stage(self,in_channels, out_channels, num_blocks, stride):
        blocks = []
        for _ in range(num_blocks): 
            blocks.append(ConvBlock(in_channels, out_channels, stride))
            # this updates the channels for the next block
            in_channels = out_channels
        return nn.Sequential(*blocks)
    
    def forward(self, x):
        x = self.stem(x)
        for layer in self.layers: 
            x = layer(x)
        # this is the global average pooling which means ... Explain 
        x = nn.functional.adaptive_avg_pool2d(x, 1).view(x.size(0), -1)
        s = self.fc(x)
        return x

# train the input 
if __name__ == "__main__":
    model = RegNet()
    # here it goes the sample input 
    #x = 
    output = model(x)
    # testing the outputshape 
    print(output.shape)