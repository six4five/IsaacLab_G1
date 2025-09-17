该仓库基于截止至2025年9月9日的[IsaacLab](https://github.com/isaac-sim/IsaacLab.git)与[unitree_rl_lab](https://github.com/unitreerobotics/unitree_rl_lab.git)。其中跟着unitree_rl_lab中下载的unitree_model与unitree_sdk2也是截至2025年9月9日版本的。

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

## isaaclab中actions元素索引对应的具体关节

![1](/unitree_rl_lab/z_image/actions00-15.jpeg )
![1](/unitree_rl_lab/z_image/actions16-28.jpeg )