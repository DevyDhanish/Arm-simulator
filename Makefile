default:
	g++ -c src/imgui/imgui_demo.cpp -o	build/a.o
	g++ -c src/imgui/imgui_draw.cpp -o 	build/b.o
	g++ -c src/imgui/imgui_tables.cpp -o build/c.o
	g++ -c src/imgui/imgui_widgets.cpp -o build/d.o
	g++ -c src/imgui/imgui.cpp -o build/e.o
	g++ -c include/imgui/backends/imgui_impl_glfw.cpp -o build/f.o
	g++ -c include/imgui/backends/imgui_impl_opengl2.cpp -o build/g.o
	ar rcs library/libimgui.a build/*.o
	g++ src/todo.cpp -Iinclude -Llibrary -limgui -lglfw3 -lopengl32 -lgdi32 -luser32 -o bin/todo