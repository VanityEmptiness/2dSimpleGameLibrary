#include "SDLApplication.h"
#include "GameManager/Scene.h"

SDLApplication::SDLApplication(const std::string& title, const float width, const float height) 
	: window_name{ title }, width{ width }, height{ height }
{   
}

bool SDLApplication::Run()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return false;
    }

    this->window_flags = (SDL_WindowFlags)(ApplicationSettings::VideoSettings::is_resizable ? (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI) : SDL_WINDOW_ALLOW_HIGHDPI);
    this->window = SDL_CreateWindow(this->window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, window_flags);

    this->renderer = SDL_CreateRenderer(this->window, -1, (ApplicationSettings::VideoSettings::enable_vsync ? (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED) : SDL_RENDERER_ACCELERATED));
    if (renderer == NULL)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return false;
    }

    //Set the renderer to the screen manager
    scene_manager->renderer = this->renderer;
    scene_manager->texture_manager = new TextureSet(this->renderer);
    game_handler->OnLoad();

    //Imgui Render Implementation
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(this->window, this->renderer);
    ImGui_ImplSDLRenderer_Init(this->renderer);

    //Font Implementation
    io.Fonts->AddFontFromFileTTF("SDLGameLib/Resources/Fonts/MuseoSansCyrl700.ttf", ApplicationSettings::DebugMenuSettings::font_size);

    return true;
}

void SDLApplication::UpdateRender()
{
    while (this->is_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                this->is_running = false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                this->is_running = false;
            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
                event_handler->_Dispatch(event);
        }

        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();

        //Imgui Render

        //Imgui Style Setup
        ImGui::StyleColorsDark();

        auto& imgui_style = ImGui::GetStyle();

        imgui_style.WindowRounding = 11.000f;
        imgui_style.WindowTitleAlign = ImVec2(0.470f, 0.690f);
        imgui_style.ChildRounding = 8.000f;
        imgui_style.PopupRounding = 8.000f;
        imgui_style.FramePadding = ImVec2(5.000f, 2.000f);
        imgui_style.FrameRounding = 8.000f;
        imgui_style.GrabRounding = 8.000f;
        imgui_style.TabRounding = 7.000f;

        imgui_style.Colors[ImGuiCol_Text] = ImVec4(0.988f, 0.976f, 0.976f, 1.000f);
        imgui_style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.492f, 0.492f, 0.492f, 1.000f);
        imgui_style.Colors[ImGuiCol_WindowBg] = ImVec4(0.148f, 0.148f, 0.148f, 0.940f);
        imgui_style.Colors[ImGuiCol_ChildBg] = ImVec4(0.005f, 0.005f, 0.005f, 0.000f);
        imgui_style.Colors[ImGuiCol_PopupBg] = ImVec4(0.079f, 0.078f, 0.078f, 0.940f);
        imgui_style.Colors[ImGuiCol_Border] = ImVec4(0.296f, 0.295f, 0.295f, 0.992f);
        imgui_style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.173f, 0.171f, 0.171f, 0.000f);
        imgui_style.Colors[ImGuiCol_FrameBg] = ImVec4(0.296f, 0.292f, 0.292f, 0.992f);
        imgui_style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.378f, 0.376f, 0.376f, 0.992f);
        imgui_style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.292f, 0.292f, 0.292f, 0.992f);
        imgui_style.Colors[ImGuiCol_TitleBg] = ImVec4(0.116f, 0.114f, 0.114f, 1.000f);
        imgui_style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.300f, 0.297f, 0.297f, 0.992f);
        imgui_style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.144f, 0.143f, 0.143f, 1.000f);
        imgui_style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.152f, 0.152f, 0.152f, 1.000f);
        imgui_style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.132f, 0.131f, 0.131f, 1.000f);
        imgui_style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.312f, 0.311f, 0.311f, 1.000f);
        imgui_style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.406f, 0.405f, 0.405f, 1.000f);
        imgui_style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.513f, 0.511f, 0.511f, 1.000f);
        imgui_style.Colors[ImGuiCol_CheckMark] = ImVec4(0.354f, 0.726f, 0.652f, 1.000f);
        imgui_style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.355f, 0.722f, 0.648f, 1.000f);
        imgui_style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.397f, 0.828f, 0.742f, 1.000f);
        imgui_style.Colors[ImGuiCol_Button] = ImVec4(0.357f, 0.726f, 0.651f, 1.000f);
        imgui_style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.343f, 0.820f, 0.724f, 1.000f);
        imgui_style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.407f, 0.894f, 0.795f, 1.000f);
        imgui_style.Colors[ImGuiCol_Header] = ImVec4(0.296f, 0.295f, 0.295f, 0.992f);
        imgui_style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.357f, 0.354f, 0.354f, 0.992f);
        imgui_style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.447f, 0.445f, 0.445f, 0.992f);
        imgui_style.Colors[ImGuiCol_Separator] = ImVec4(0.206f, 0.204f, 0.204f, 0.500f);
        imgui_style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.206f, 0.204f, 0.204f, 0.502f);
        imgui_style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.210f, 0.208f, 0.208f, 0.502f);
        imgui_style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.352f, 0.722f, 0.647f, 1.000f);
        imgui_style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.402f, 0.824f, 0.739f, 1.000f);
        imgui_style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.406f, 0.824f, 0.741f, 1.000f);
        imgui_style.Colors[ImGuiCol_Tab] = ImVec4(0.360f, 0.726f, 0.652f, 1.000f);
        imgui_style.Colors[ImGuiCol_TabHovered] = ImVec4(0.316f, 0.648f, 0.598f, 1.000f);
        imgui_style.Colors[ImGuiCol_TabActive] = ImVec4(0.223f, 0.537f, 0.490f, 1.000f);
        imgui_style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.355f, 0.722f, 0.648f, 1.000f);
        imgui_style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.356f, 0.730f, 0.654f, 1.000f);
        imgui_style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.198f, 0.200f, 0.202f, 0.350f);

        //ImGui Render Fragment
        ImGui::NewFrame();

        if (ApplicationSettings::is_debugging)
            this->RenderImgui();

        ImGui::Render();

        SDL_SetRenderDrawColor(
            this->renderer, 
            (Uint8)(this->background_render_clear_color.x * 255), 
            (Uint8)(this->background_render_clear_color.y * 255), 
            (Uint8)(this->background_render_clear_color.z * 255), 
            (Uint8)(this->background_render_clear_color.w * 255)
        );
        SDL_RenderClear(this->renderer);
        //Sdl Render
        this->RenderSDL();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(this->renderer);
    }
}

void SDLApplication::Destroy()
{
    //Game Cleanup
    delete scene_manager;

    //ImGui Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    //Sdl Cleanup
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void SDLApplication::RenderImgui()
{
#pragma region Profiler

    ImGui::Begin("Profiler");

    ImGui::Text("Rendering: (%.1f FPS)", ImGui::GetIO().Framerate);
    ImGui::Text("Rendering Elapsed Time: (%.3f ms/frame)", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("Rendered Scene Objects: (%llu)", scene_manager->current_scene->GetSceneObjectsRenderList().size());
    ImGui::Text("Game Update: (%f FPS)", game_handler->fps);
    ImGui::Text("Game Update Elapsed Time: (%f sec/frame)", game_handler->delta_time);

    PROCESS_MEMORY_COUNTERS_EX process_memory_counters;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&process_memory_counters, sizeof(process_memory_counters));
    size_t process_used_virtual_memory = process_memory_counters.PrivateUsage;
    ImGui::Text("Committed Memory: (%llu MB)", ((process_used_virtual_memory / 1024) / 1024));

    ImGui::End();

#pragma endregion
    
#pragma region SceneManager

    ImGui::Begin("Scenes");
    static char add_scene_input_buffer[256];

    //Display Add Scenes input 
    ImGui::InputText("Add Scene", add_scene_input_buffer, IM_ARRAYSIZE(add_scene_input_buffer));
    ImGui::SameLine();
    if (ImGui::SmallButton("Add"))
        if ((std::string)add_scene_input_buffer != "")
            scene_manager->AddScene(add_scene_input_buffer);

    //Display Available Scenes
    ImGui::Separator();
    ImGui::TextDisabled("Available Scenes:");
    UINT scenes_iterathor = 0;
    std::vector<std::string> scenes_to_delete;

    for (const auto& scene : scene_manager->GetAllScenes())
    {
        scenes_iterathor++;
        ImGui::Text(scene.first.c_str());
        if (&scene.second == scene_manager->current_scene)
            continue;
        ImGui::SameLine();
        if (ImGui::SmallButton(((std::string)"Switch##" + std::to_string(scenes_iterathor)).c_str()))
            scene_manager->SwitchScene(scene.first);
        ImGui::SameLine();
        if (ImGui::SmallButton(((std::string)"Remove##" + std::to_string(scenes_iterathor)).c_str()))
            scenes_to_delete.push_back(scene.first);
    }

    if (scenes_to_delete.size() > 0)
        for (size_t i = 0; i < scenes_to_delete.size(); i++)
            scene_manager->RemoveScene(scenes_to_delete[i]);

    scenes_to_delete.clear();

    ImGui::End();
    
#pragma endregion

    static std::string current_selected_scene_object = "";
    static Vec2 current_selected_scene_object_pos = { 0 , 0 };
    bool has_current_selected_object_changed = false;

#pragma region CurrentSceneMenu
    //Block Scope 
    {
        ImGui::Begin("Current Scene");

        //Display the current scene name
        ImGui::TextDisabled(scene_manager->current_scene->scene_name.c_str());

        static char add_scene_object_input_buffer[256];

        //Display New Scene Objects input handler
        ImGui::InputText("Add Scene Object", add_scene_object_input_buffer, IM_ARRAYSIZE(add_scene_object_input_buffer));
        ImGui::SameLine();
        if (ImGui::SmallButton("Add"))
            if ((std::string)add_scene_object_input_buffer != "")
                scene_manager->current_scene->AddSceneObject(add_scene_object_input_buffer);

        //Display Available Scenes
        ImGui::Separator();
        ImGui::TextDisabled("Available Objects:");
        UINT scene_objects_iterathor = 0;
        std::vector<std::string> scene_objects_to_delete;

        for (const auto& object : scene_manager->current_scene->GetSceneObjectsMap())
        {
            scene_objects_iterathor++;
            ImGui::Text(object.first.c_str());

            ImGui::SameLine();
            if (ImGui::SmallButton(((std::string)"Select##" + std::to_string(scene_objects_iterathor)).c_str()))
            {
                current_selected_scene_object = object.first;
                current_selected_scene_object_pos = { 0 , 0 };
                has_current_selected_object_changed = true;
            }
            ImGui::SameLine();
            if (ImGui::SmallButton(((std::string)"Remove##" + std::to_string(scene_objects_iterathor)).c_str()))
                scene_objects_to_delete.push_back(object.first);
        }

        if (scene_objects_to_delete.size() > 0)
            for (size_t i = 0; i < scene_objects_to_delete.size(); i++)
                scene_manager->current_scene->RemoveSceneObject(scene_objects_to_delete[i]);

        scene_objects_to_delete.clear();

        ImGui::End();
    }
#pragma endregion

#pragma region CurrentSelectedSceneObject
    //Block Scope 
    {
        if (current_selected_scene_object.size() > 1)
            if (scene_manager->current_scene->HasSceneObject(current_selected_scene_object))
            {
                if (has_current_selected_object_changed)
                {
                    has_current_selected_object_changed = false;
                    current_selected_scene_object_pos = scene_manager->current_scene->GetSceneObject(current_selected_scene_object)->GetPosition();
                }

                ImGui::Begin(current_selected_scene_object.c_str());
                ImGui::DragFloat("X", &current_selected_scene_object_pos.x, 1.0f, -100000, 100000, "%.2f");
                ImGui::DragFloat("Y", &current_selected_scene_object_pos.y, 1.0f, -100000, 100000, "%.2f");
                if (
                    scene_manager->current_scene->GetSceneObject(current_selected_scene_object)->GetPosition().x != current_selected_scene_object_pos.x ||
                    scene_manager->current_scene->GetSceneObject(current_selected_scene_object)->GetPosition().y != current_selected_scene_object_pos.y
                    )
                {
                    scene_manager->current_scene->GetSceneObject(current_selected_scene_object)->SetPosition(current_selected_scene_object_pos);
                }
                ImGui::End();
            }
            else if (scene_manager->current_scene->GetSceneObjectsMap().size() > 0)
                current_selected_scene_object = scene_manager->current_scene->GetSceneObjectsMap().begin()->first;
            else
                current_selected_scene_object = "";
    }

#pragma endregion

}

void SDLApplication::RenderSDL()
{
    scene_manager->current_scene->Render();
}

void SDLApplication::Update()
{
    clock_t current_ticks, delta_ticks;
    clock_t fps = 0;
    
    std::chrono::steady_clock::time_point current_cpu_update_frame_time_point = std::chrono::steady_clock::now();

    while (true)
    {
        if (!application->is_running)
            return;

        current_ticks = clock();
        
        //Update Physics
        scene_manager->current_scene->UpdateCollisionDetection();
        scene_manager->current_scene->UpdateMovementPhysics();

        //Finally Calls User Defined Game Update
        game_handler->OnUpdate();

        std::chrono::steady_clock::time_point cpu_update_frame_end_time_point = std::chrono::steady_clock::now();

        delta_ticks = clock() - current_ticks;
        
        double elapsed_time = ((double)std::chrono::duration_cast<std::chrono::milliseconds>(cpu_update_frame_end_time_point - current_cpu_update_frame_time_point).count());
        elapsed_time /= (1000.0);
        game_handler->delta_time = elapsed_time;

        current_cpu_update_frame_time_point = std::chrono::steady_clock::now();

        if (delta_ticks > 0)
        {
            fps = CLOCKS_PER_SEC / delta_ticks;
            game_handler->fps = fps;
        }

        Sleep(1);
    }
}