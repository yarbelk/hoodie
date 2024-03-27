# Hoodie - Visual Scripting Procedural Geometry for Godot Engine 4

![hoodie_logo_2023_1_Page 3](https://github.com/GreenCrowDev/hoodie/assets/62719360/dcb5f7d7-e848-45fb-bf7f-4bcee3c27a38)

Hoodie is a **plugin** for Godot Engine 4 that offers a **visual scripting** interface for generating **procedural geometry**.

Design parametric mesh geometry using a visual scripting language and iterate quickly over changes:
create algorithms with nodes and utilize parameters to customize and fine-tune the generated mesh for your own use cases.

## Support this project

Hoodie is an open-source project licensed under the MIT License, free to use in your projects.
If you find it useful for yourself and the community, you may consider supporting its development through [this Gumroad page](https://greencrowdev.gumroad.com/l/hoodie), which also offers additional perks.

## Devlogs

This project also has a series of dedicated video devlogs that you can watch [here on YouTube](https://www.youtube.com/watch?v=_GJQfH5vNs8&list=PL_rPTnOU23F0o3Mf9EDbX-SqA3ET970jT&pp=gAQBiAQB).

## Installation

You can start using Hoodie by directly downloading binary files, or you can compile it yourself.

### Direct Download

At this time only Windows is supported, but you can [compile it yourself](#compile-from-source) to make it work on different platforms.

1. Download the latest binary from the [Releases](https://github.com/GreenCrowDev/hoodie/releases) page on GitHub.
2. Open the folder of your Godot Engine game project, and create a `bin` folder if it doesn't exists yet.
3. Copy the downloaded files in the newly created `bin` folder. The folder structure should now look something like this:

```
<your-project-folder-name>/
│
├── .godot/
│
├── bin/
│   ├── hoodie.gdextension
│   ├── hoodie.svg
│   ├── libhoodie.windows.editor.dev.x86_64.dll
│   ├── libhoodie.windows.template_release.x86_64.dll
```

4. You're now ready to go! Read [Getting Started](#getting-started) for a quick tutorial of the plugin.

### Compile from Source

In case your platform isn't included in the shipped binaries, you need to compile the project by yourself from source.

Since this is a Godot GDExtension plugin, the compiling procedure is the same as the one for Godot Engine itself, as stated [here](https://docs.godotengine.org/it/4.x/tutorials/scripting/gdextension/gdextension_cpp_example.html#setting-up-the-project) on the official documentation.
On this [page](https://docs.godotengine.org/it/4.x/contributing/development/compiling/index.html#toc-devel-compiling) you'll find detailed guides about how to build for each platform.

Generally you want these tools to be installed:

- A C++ compiler
- Python 3.6+
- SCons 3.0+

Once you managed to install all the necessary tools, follow these next steps:

1. Clone this project repository.
2. Open the terminal and navigate to the repository folder.
3. Launch command `scons target=editor dev_mode=yes dev_build=yes`. If you want a more optimized build, use `scons target=editor` instead, but remember to change the name of the resulting binary adding `dev` to it like in this example: `libhoodie.linux.editor.x86_64.so` -> `libhoodie.linux.editor.dev.x86_64.so` (N.B. SCons will automatically recognize the OS you're working on, but you can specify it as an additional parameters if needed, following the Godot docs mentioned above).
4. (Optional) Launch command `scons target=template_release` to generate the release template binaries, in case you intend to build your game project with Hoodie in it.
5. The resulting binary files will be located in the repository at the `hoodie/demo/bin` folder.
6. At this point you can just follow the [Direct Download section](#direct-download) starting from **step 2** (you simply need to put the generated binaries in the correct game project folder).

## Getting Started

<img src="https://github.com/GreenCrowDev/hoodie/assets/62719360/173d784f-09a8-4115-93d0-1a6b11e0e54d" width="480">

Before you can use Hoodie's visual scripting interface, you need to set up the right nodes, then you'll be ready to go!

1. If you haven't already done so, create a new **3D Scene** and open it.
2. **'Add Child Node...'** with **CTRL+A** or the **'+'** button from the Scene panel, and choose `MeshInstance3D`.
3. Once you have the new `MeshInstance3D` selected, head over to the **Inspector** and create a new `HoodieMesh` through the **'Mesh'** property, selecting **'New HoodieMesh'**.
4. Now that the **'Mesh'** property is filled with a new `HoodieMesh`, click on the `HoodieMesh` option button to start editing it.
5. The **Hoodie** panel will appear in the bottom control panel, and there you will be able to use visual scripting to create your algorithms through nodes.
6. Start by adding an `Output` node with the **'Add node...'** popup menu at the top left of the Hoodie editor.
7. `Add node... > Mesh > Primitives > Mesh Grid`.
8. Connect the `Mesh` output slot of the `Mesh Grid` node to the `Geometry` input slot of the `Output` node.
9. You will now see a 1x1 plane show up in the viewport.
10. **Congratulations!** You just created your first Hoodie procedural geometry! 🥳
11. You can tweak the size of the plane connecting `Add node... > Input > Constant > Input Value` to the `Mesh Grid`, and see its changes in real time.

### Extrude a line along a path (road-like geometry)

<img src="https://github.com/GreenCrowDev/hoodie/assets/62719360/0b24efc5-8e55-4e3e-be4c-673566ff1411" width="480">

1. Create a `Path3D` node in your **3D Scene** and proceed to model a curve with the designated tools.
2. While the `Path3D` is selected, go to the **Inspector** and open the `Curve3D` option button, then click on **Copy**.
3. Go back to the Hoodie editor, and create a `Input Curve3D` node from `Add node... > Input > Input Curve3D`.
4. Go to the **Inspector**, and you'll see a new property group has appeared: **Inputs**.
5. Expand the **Inputs** property group and a `Curve3D` property will appear, where the label name is the _id_ of the `Input Curve3D` node you added earlier.
6. Click on the `Curve3D` property option button, and then click on **Paste** in order to paste the copied `Curve3D`.
7. Now that the curve has been correctly referenced, we need a couple of other nodes to generate a geometry along the path.
8. `Add node... > Mesh > Primitives > Mesh Line`: this will be the extruded geometry along the path.
9. `Add node... > Curve > Operations > Curve to Mesh`.
10. Connect the `Curve3D` output slot of the `Input Curve3D` node to the `Curve3D` input slot of the `Curve to Mesh` node.
11. Connect the `Mesh` output slot of the `Mesh Line` node to the `Profile` input slot of the `Curve to Mesh` node.
12. Connect the `Mesh` output slot of the `Curve to Mesh` node to the `Geometry` input slot of the `Output` node.
13. You will now see a mesh along the path you designed earlier! 🥳
14. You can now tweak the input values for your needs, for example with a `Add node.. > Input > Constant > Input Vector3D` node.

### Create a custom collider

Creating a custom collider for your HoodieMesh is very easy and straightforward!

<img src="https://github.com/GreenCrowDev/hoodie/assets/62719360/49b804e9-8b3b-48b8-b4c5-0b4d273b0d6f" width="480">

1. After generating your custom `HoodieMesh`, click on the `Mesh` menu button in the toolbar (refer to the image above).
2. Choose `Create Trimesh Static Body`.
3. You now have a collider mesh identical to your generated `HoodieMesh`! Remember, the collider will not update automatically as you modify your `HoodieMesh`. You'll have to recreate the collider each time you make changes.

## Known issues

- The release template has not been tested yet.
- Capabilities are limited by the small number of nodes, but the list is being updated with each release!

## Bugs, Help, Feedback and Suggestions

Feel free to open an issue here on GitHub if you find a bug 😊

To submit feedback, suggestions, or get further help, [join the Discord server](https://discord.gg/mnEh4KB7P2). You'll find the appropriate _Hoodie_ category where you can join the discussion!

## Sponsors

Interested in sponsoring this project?
Get featured in this section with your logo and link 👀
Take a look [here](https://greencrowdev.gumroad.com/l/hoodie).

## Special thanks

Special thanks to:

- [Bastiaan Olij](https://github.com/BastiaanOlij) for creating [gdprocmesh](https://github.com/BastiaanOlij/gdprocmesh/), which served as a reference at the start of this project journey.
- [Zylann](https://github.com/Zylann) and [Naros](https://github.com/Naros) for their assistance through the Godot Engine official Discord server.
