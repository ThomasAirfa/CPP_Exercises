<<<<<<< HEAD
<<<<<<< HEAD
#!/usr/bin/python3

# Usage:
# python3 ./prepare_station.py [tpVX]  where V is in {r,n} and X in {1,2,3,4}

import os
import shutil
import subprocess
import sys
import tempfile
import json
from stat import S_IRUSR, S_IRGRP, S_IROTH, S_IWUSR, S_IWGRP, S_IWOTH
from zipfile import ZipFile


usage_line= """Usage:
\t python3 ./prepare_station.py [tpVX]  where V is in {r,n} and X in {1,2,3,4}
"""

sujet_dir = os.path.join(os.environ["HOME"], "SUJET")
exam_dir = os.path.join(os.environ["HOME"], "EXAM")
tmp_work_dir = os.path.join(tempfile.gettempdir(), "CPP")
extraction_dir = os.path.join(tmp_work_dir, ".extraction")
build_dir = os.path.join(tmp_work_dir, "build")
codium_data_dir = os.path.join(tmp_work_dir, "codium_data")
archive_ext = ".zip";


# 1a. Find the archive in SUJET folder.
if len(sys.argv) < 2:
    print(f"No argument given, trying to find archive in {sujet_dir}")
    acceptable_files = ['tp'+n+str(i)+archive_ext for n in ['r','n'] for i in range(1,5)]+[x+archive_ext for x in ['tp04','tp08','tp12']]
    entry=[]
    found=[]
    with os.scandir(sujet_dir) as it:
        for entry in it:
            if entry.name in acceptable_files:
                found.append(entry.name);
    if (len(found) == 1):
        archive_name = found[0]
        archive_basename = archive_name[:-4]
        print (f"\tOne acceptable file found: {archive_name}")
    else:
        if (len(found) >= 2):
            print("\tSeveral acceptable files found: {found}")
            print("\tPlease specify which one to use.")
        else:
            print("\tNo acceptable file found.")
        print(usage_line)
        exit(1)
# 1b. Find the archive in SUJET folder.
elif len(sys.argv) == 2:
    archive_basename = sys.argv[1]
    archive_name = archive_basename+archive_ext
    found = False;
    with os.scandir(sujet_dir) as it:
        for entry in it:
            if entry.name ==  archive_name:
                found = True;
                break;
    if not found:
        print(f"No archive {archive_basename} found in {sujet_dir}")
# 1c. Fail if incorrect number of arguments
else:
        print(usage_line)
        exit(2)


    

# 2. Extract all the archive in the TMPDIR folder (if it does not already exists).
if not os.path.exists(tmp_work_dir):
    print(f"Creating directory {tmp_work_dir}")
    os.mkdir(tmp_work_dir)

if not os.path.exists(extraction_dir):
    print(f"Creating directory {extraction_dir} for extraction")
    os.mkdir(extraction_dir)
    print(f"Extracting in {extraction_dir} archive {archive_name} from directory {sujet_dir}")
    with ZipFile(os.path.join(sujet_dir, archive_name), 'r') as exam_archive:
        exam_archive.extractall(extraction_dir)
else:
    print(f"Directory {extraction_dir} already exists. Not extracting")

subdir_name = archive_basename #FIXME: we could check that this is correct.
exam_subdir=os.path.join(exam_dir,subdir_name)
local_build_dir=os.path.join(exam_subdir,"build")


# 3. Update the .vscode/settings.json
print("Handling workspace VS Codium setting")
extraction_subdir = os.path.join(extraction_dir, subdir_name)
extraction_settings_dir = os.path.join(extraction_subdir,".vscode")
extraction_settings_file = os.path.join(extraction_settings_dir,"settings.json")
extraction_settings_content = { 
    'clangd.arguments': [f"--compile-commands-dir={build_dir}"],
    "terminal.integrated.cwd": f"{build_dir}"
}
if not os.path.exists(extraction_settings_dir):
    print(f"\tCreating {extraction_settings_dir}")
    os.mkdir(extraction_settings_dir)
else:
    print(f"\tDirectory {extraction_settings_dir} already exists")

if not os.path.exists(extraction_settings_file):
    print(f"\tCreating {extraction_settings_file}")
    d = dict()
else:
    print(f"\tFile {extraction_settings_file} exists, updating it")
    with open(extraction_settings_file, 'r') as file:
        try:
            d = json.load(file);
        except Exception as e:
            print(f"\tProblem decoding json file {extraction_settings_file}:") 
            print(e)
            print("Aborting")
            exit(3)
d.update(extraction_settings_content)
with open(extraction_settings_file, 'w') as file:
    json.dump(d, file, indent=4)
    


# 3. Copying the subject to its correct location if it has not been copied there already.
if not os.path.exists(exam_subdir):
    print(f"Moving {subdir_name} from {extraction_dir} to {exam_dir}.")
    shutil.copytree(extraction_subdir, exam_subdir)
else:
    print(f"Directory {exam_subdir} already exists. It will not be replaced.")


# 4. Create the backup folder
backup_dir = os.path.join(exam_subdir, "backup")
if not os.path.exists(backup_dir): 
    print(f"Creating backup directory {backup_dir}.")
    os.mkdir(backup_dir)
else:
    print(f"Backup directory {backup_dir}, already exists.")


# 5. Put everything in readonly mode, except the src/ folder, the backup/ folder and the files inside of it
#print(f"For security, making all files read-only if they are not in src or backup directories.")
#def is_in_src_or_backup(file: str) -> bool:
#    file_path = os.path.abspath(file)
#    setting_path = os.path.join(os.path.abspath(exam_subdir), ".vscode")
#    ex_path = os.path.join(os.path.abspath(exam_subdir), "ex")
#    backup_path = os.path.join(os.path.abspath(exam_subdir),  "backup")
#    if file_path.startswith(backup_path):
#        return True
#    if file_path.startswith(setting_path):
#        return True
#    if not file_path.startswith(ex_path):
#        return False
#    path_comps = file_path.replace(ex_path, "").split(os.path.sep)
#    return len(path_comps) > 1 and path_comps[1] == "src"
#for root, dirs, files in os.walk(exam_subdir):
#    elements = dirs + files
#    for name in elements:
#        full_path = os.path.join(root, name)
#        if not is_in_src_or_backup(full_path):
#            print(f"\tMaking {full_path} read-only")
#            rights = os.stat(full_path).st_mode
#            os.chmod(full_path, rights & ~(S_IWUSR|S_IWGRP|S_IWOTH))



# 6. Configure the CMake project
print(f"Configuring the project in {build_dir} with CMake")
configure_task = subprocess.Popen(["cmake", "-S", exam_subdir, "-B", build_dir])
configure_task.wait()


# 7. Build Catch2
print(f"Building Catch external library (could take some time the first time)")
catch2_build_task = subprocess.Popen(["cmake", "--build", build_dir, "--target", "Catch2WithMain", "-j"])
catch2_build_task.wait()


# 8. Open VS Codium in the right folder and with the right configuration
print(f"Opening VS Codium correctly")
if not os.path.exists(codium_data_dir): 
    print(f"\tCreating VS Codium data directory {codium_data_dir}")
    os.mkdir(codium_data_dir)
else:
    print(f"\tVS Codium data directory {codium_data_dir} already exists")

#patched_env = {**os.environ, 'XDG_CACHE_HOME': f'{codium_data_dir}' }
subprocess.Popen(["codium", exam_subdir, "--user-data-dir", codium_data_dir]) #, env=patched_env)



=======
version https://git-lfs.github.com/spec/v1
oid sha256:2d9179671c17d40b6989d8c8b522c2d9f133549577849b17dc7711f6617240a3
size 7053
>>>>>>> b028e23 (The script will work if /tmp/CPP/.extraction exists but /tmp/CPP/.extraction/XXX doest not)
=======
<<<<<<< HEAD
version https://git-lfs.github.com/spec/v1
oid sha256:2d9179671c17d40b6989d8c8b522c2d9f133549577849b17dc7711f6617240a3
size 7053
=======
=======
>>>>>>> 55e7153 (The script will work if /tmp/CPP/.extraction exists but /tmp/CPP/.extraction/XXX doest not)
#!/usr/bin/python3

# Usage:
# python3 ./prepare_station.py [tpVX]  where V is in {r,n} and X in {1,2,3,4}

import os
import shutil
import subprocess
import sys
import tempfile
import json
from stat import S_IRUSR, S_IRGRP, S_IROTH, S_IWUSR, S_IWGRP, S_IWOTH
from zipfile import ZipFile


usage_line= """Usage:
\t python3 ./prepare_station.py [tpVX]  where V is in {r,n} and X in {1,2,3,4}
"""

sujet_dir = os.path.join(os.environ["HOME"], "SUJET")
exam_dir = os.path.join(os.environ["HOME"], "EXAM")
tmp_work_dir = os.path.join(tempfile.gettempdir(), "CPP")
extraction_dir = os.path.join(tmp_work_dir, ".extraction")
build_dir = os.path.join(tmp_work_dir, "build")
codium_data_dir = os.path.join(tmp_work_dir, "codium_data")
archive_ext = ".zip";


# 1a. Find the archive in SUJET folder.
if len(sys.argv) < 2:
    print(f"No argument given, trying to find archive in {sujet_dir}")
    acceptable_files = ['tp'+n+str(i)+archive_ext for n in ['r','n'] for i in range(1,5)]+[x+archive_ext for x in ['tp04','tp08','tp12']]
    entry=[]
    found=[]
    with os.scandir(sujet_dir) as it:
        for entry in it:
            if entry.name in acceptable_files:
                found.append(entry.name);
    if (len(found) == 1):
        archive_name = found[0]
        archive_basename = archive_name[:-4]
        print (f"\tOne acceptable file found: {archive_name}")
    else:
        if (len(found) >= 2):
            print("\tSeveral acceptable files found: {found}")
            print("\tPlease specify which one to use.")
        else:
            print("\tNo acceptable file found.")
        print(usage_line)
        exit(1)
# 1b. Find the archive in SUJET folder.
elif len(sys.argv) == 2:
    archive_basename = sys.argv[1]
    archive_name = archive_basename+archive_ext
    found = False;
    with os.scandir(sujet_dir) as it:
        for entry in it:
            if entry.name ==  archive_name:
                found = True;
                break;
    if not found:
        print(f"No archive {archive_basename} found in {sujet_dir}")
# 1c. Fail if incorrect number of arguments
else:
        print(usage_line)
        exit(2)


    

# 2. Extract all the archive in the TMPDIR folder (if it does not already exists).
if not os.path.exists(tmp_work_dir):
    print(f"Creating directory {tmp_work_dir}")
    os.mkdir(tmp_work_dir)

if not os.path.exists(extraction_dir):
    print(f"Creating directory {extraction_dir} for extraction")
    os.mkdir(extraction_dir)
    print(f"Extracting in {extraction_dir} archive {archive_name} from directory {sujet_dir}")
    with ZipFile(os.path.join(sujet_dir, archive_name), 'r') as exam_archive:
        exam_archive.extractall(extraction_dir)
else:
    print(f"Directory {extraction_dir} already exists. Not extracting")

subdir_name = archive_basename #FIXME: we could check that this is correct.
exam_subdir=os.path.join(exam_dir,subdir_name)
local_build_dir=os.path.join(exam_subdir,"build")


# 3. Update the .vscode/settings.json
print("Handling workspace VS Codium setting")
extraction_subdir = os.path.join(extraction_dir, subdir_name)
extraction_settings_dir = os.path.join(extraction_subdir,".vscode")
extraction_settings_file = os.path.join(extraction_settings_dir,"settings.json")
extraction_settings_content = { 
    'clangd.arguments': [f"--compile-commands-dir={build_dir}"],
    "terminal.integrated.cwd": f"{build_dir}"
}
if not os.path.exists(extraction_settings_dir):
    print(f"\tCreating {extraction_settings_dir}")
    os.mkdir(extraction_settings_dir)
else:
    print(f"\tDirectory {extraction_settings_dir} already exists")

if not os.path.exists(extraction_settings_file):
    print(f"\tCreating {extraction_settings_file}")
    d = dict()
else:
    print(f"\tFile {extraction_settings_file} exists, updating it")
    with open(extraction_settings_file, 'r') as file:
        try:
            d = json.load(file);
        except Exception as e:
            print(f"\tProblem decoding json file {extraction_settings_file}:") 
            print(e)
            print("Aborting")
            exit(3)
d.update(extraction_settings_content)
with open(extraction_settings_file, 'w') as file:
    json.dump(d, file, indent=4)
    


# 3. Copying the subject to its correct location if it has not been copied there already.
if not os.path.exists(exam_subdir):
    print(f"Moving {subdir_name} from {extraction_dir} to {exam_dir}.")
    shutil.copytree(extraction_subdir, exam_subdir)
else:
    print(f"Directory {exam_subdir} already exists. It will not be replaced.")


# 4. Create the backup folder
backup_dir = os.path.join(exam_subdir, "backup")
if not os.path.exists(backup_dir): 
    print(f"Creating backup directory {backup_dir}.")
    os.mkdir(backup_dir)
else:
    print(f"Backup directory {backup_dir}, already exists.")


# 5. Put everything in readonly mode, except the src/ folder, the backup/ folder and the files inside of it
#print(f"For security, making all files read-only if they are not in src or backup directories.")
#def is_in_src_or_backup(file: str) -> bool:
#    file_path = os.path.abspath(file)
#    setting_path = os.path.join(os.path.abspath(exam_subdir), ".vscode")
#    ex_path = os.path.join(os.path.abspath(exam_subdir), "ex")
#    backup_path = os.path.join(os.path.abspath(exam_subdir),  "backup")
#    if file_path.startswith(backup_path):
#        return True
#    if file_path.startswith(setting_path):
#        return True
#    if not file_path.startswith(ex_path):
#        return False
#    path_comps = file_path.replace(ex_path, "").split(os.path.sep)
#    return len(path_comps) > 1 and path_comps[1] == "src"
#for root, dirs, files in os.walk(exam_subdir):
#    elements = dirs + files
#    for name in elements:
#        full_path = os.path.join(root, name)
#        if not is_in_src_or_backup(full_path):
#            print(f"\tMaking {full_path} read-only")
#            rights = os.stat(full_path).st_mode
#            os.chmod(full_path, rights & ~(S_IWUSR|S_IWGRP|S_IWOTH))



# 6. Configure the CMake project
print(f"Configuring the project in {build_dir} with CMake")
configure_task = subprocess.Popen(["cmake", "-S", exam_subdir, "-B", build_dir])
configure_task.wait()


# 7. Build Catch2
print(f"Building Catch external library (could take some time the first time)")
catch2_build_task = subprocess.Popen(["cmake", "--build", build_dir, "--target", "Catch2WithMain", "-j"])
catch2_build_task.wait()


# 8. Open VS Codium in the right folder and with the right configuration
print(f"Opening VS Codium correctly")
if not os.path.exists(codium_data_dir): 
    print(f"\tCreating VS Codium data directory {codium_data_dir}")
    os.mkdir(codium_data_dir)
else:
    print(f"\tVS Codium data directory {codium_data_dir} already exists")

#patched_env = {**os.environ, 'XDG_CACHE_HOME': f'{codium_data_dir}' }
subprocess.Popen(["codium", exam_subdir, "--user-data-dir", codium_data_dir]) #, env=patched_env)