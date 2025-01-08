import os
import json

def generate_folder_structure(root_folder, exclude_folders=None):
    """
    Gera a estrutura de pastas e arquivos em JSON.

    Args:
        root_folder (str): Caminho para a pasta raiz.
        exclude_folders (list): Lista de strings com nomes de pastas a serem ignoradas.

    Returns:
        str: Estrutura de pastas em formato JSON.
    """
    if exclude_folders is None:
        exclude_folders = []

    def walk_directory(directory):
        folder_structure = {}
        
        for item in os.listdir(directory):
            item_path = os.path.join(directory, item)
            
            if os.path.isdir(item_path):
                if item in exclude_folders:
                    continue
                folder_structure[item] = walk_directory(item_path)
            else:
                folder_structure[item] = None
        
        return folder_structure

    # Construir a estrutura da pasta
    folder_tree = {os.path.basename(root_folder): walk_directory(root_folder)}

    # Converter para JSON
    return json.dumps(folder_tree, indent=4)

# Exemplo de uso
if __name__ == "__main__":
    root = "./"  # Caminho da pasta raiz
    exclude = ["builddir", 
               "assimp",
               "Glad",
                "GLFW",
                "glm",
                "imgui",
                "spdlog",
               ]  # Pastas a serem ignoradas

    json_structure = generate_folder_structure(root, exclude)
    # Salvar a estrutura em um arquivo
    with open("folder_structure.json", "w") as f:
        f.write(json_structure)
