## 前言
该仓库基于截止至2025年9月9日的[IsaacLab](https://github.com/six4five/IsaacLab_20250909.git)与[unitree_rl_lab](https://github.com/unitreerobotics/unitree_rl_lab.git)。其中跟着unitree_rl_lab中下载的unitree_model（此仓库未上传，可在unitree_rl_lab的README中获取链接）与[unitree_sdk2](https://github.com/six4five/unitree_sdk2_20250909.git)也是截至2025年9月9日版本的。

截止该时间时，unitree_rl_lab并没有完全跟上IsaacLab的更新速度，具体错误发生在play.py中。所以此仓库的play.py文件相较于2025年9月9日unitree_rl_lab中的play.py文件有轻微差异。

具体体现在：
```python
 # extract the normalizer
    if hasattr(policy_nn, "actor_obs_normalizer"):
        normalizer = policy_nn.actor_obs_normalizer
    elif hasattr(policy_nn, "student_obs_normalizer"):
        normalizer = policy_nn.student_obs_normalizer
    else:
        normalizer = None

    # export policy to onnx/jit
    export_model_dir = os.path.join(os.path.dirname(resume_path), "exported")
    export_policy_as_jit(policy_nn, normalizer=normalizer, path=export_model_dir, filename="policy.pt")
    export_policy_as_onnx(policy_nn, normalizer=normalizer, path=export_model_dir, filename="policy.onnx")
```
```python
# reset environment
obs = env.get_observations()
```
与截至该时间的isaaclab中rsl_rl下的play.py文件保持一致。

## 在实机上运行官网底层控制实例
安装完unitree_sdk2后，按照应用开发-[快速开发](https://support.unitree.com/home/zh/G1_developer/quick_development)的教程进行。要使用网线连接电脑主机与机器人脖子后面，连接之后，给机器人开机后再修改网络配置。

按照官网教程走到最后，发现unitree_sdk2/build下根本没有bin文件夹。参考[该经验贴](https://henchat.net/unitree-go2-sdk-trouble-solution/)，**仅**作出如下调整：
```python
将unitree_sdk2/thirdparty/include/ddscxx/dds中的文件全部复制到
unitree_sdk2/thirdparty/include/dds里（即合并两文件夹），
并将unitree_sdk2/thirdparty/include/ddscxx/org整个文件夹复制到
unitree_sdk2/thirdparty/include里，
确保SDK目录是以下结构：

...
 |- thirdparty/
    |- include/
       |- dds/（与ddscxx/dds合并）
       |- org/（从ddscxx中复制）
       |- ...

```

然后清空unitree_sdk2/build文件夹中的文件，再在该目录（./unitree_sdk2/build）下重新执行：
```python
cmake ..
sudo make install
make
```
最后重新运行官网应用开发-[快速开发](https://support.unitree.com/home/zh/G1_developer/quick_development)页面的最下方代码块，注意network_interface_name要替换为具体的网卡名。

成功的效果就是机器人的脚踝一直晃来晃去。
