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
