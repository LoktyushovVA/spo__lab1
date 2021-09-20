#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;
#define MAX_DATA_LENGTH 16383

int main()
{
   //2*
    LARGE_INTEGER t_1;
    LARGE_INTEGER t_2;
    LARGE_INTEGER fr;

   //1.1
    OSVERSIONINFOA Version {};
    Version.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    GetVersionExA(&Version);

    cout << "Version is: " << Version.dwMajorVersion << "." << Version.dwMinorVersion << " ("<< Version.dwBuildNumber << ")" << endl;



//   DWORD Version = 0;
//   Version = GetVersion();
//   cout << "Version is:" << Version << endl;


    //1.2
    char system_dir[MAX_PATH];
    GetSystemDirectory(system_dir, MAX_PATH);
    cout << "System directory:" << system_dir << endl;



    //1.3
    DWORD LEN = 256;
    char name_computer[MAX_PATH];
    char name_user[MAX_PATH];
    GetComputerName(name_computer,&LEN);
    cout << "Computer name:" << name_computer <<endl;
    LEN = 256;
    GetUserName(name_user,&LEN);
    cout <<"User name:" << name_user <<endl;
    cout <<" "<< endl;

    //1.4
    char name[MAX_PATH];
    char path[MAX_PATH];
    ULARGE_INTEGER avaliable_space, total_space;
    HANDLE search = FindFirstVolume(name, sizeof(name));
    int i=1;

    do
    {
    GetVolumePathNamesForVolumeName(name,path,MAX_PATH,&LEN);
    cout<<  "Volume:"<<i<< endl;
    cout<<  "Name :" << name << endl;
    cout<<  "Path :" << path << endl;
    if (GetDiskFreeSpaceEx(path,&avaliable_space,&total_space,NULL) == 0)
         {
          cout << "no info"<<endl;
         }
    else
         {
         cout<<"avaliable_space : "<<avaliable_space.QuadPart<<endl;
         cout<<"total_space : "<<total_space.QuadPart<<endl;
         }
    i++;
    cout<<" "<<endl;
    }
    while (FindNextVolume(search, name, sizeof(name)));
    FindVolumeClose(search);

    //1.5
    HKEY key;
    DWORD dwIndex = 0;
    TCHAR lpValueName[MAX_DATA_LENGTH];
    DWORD lpcchValueName = MAX_DATA_LENGTH;
    TCHAR tcValue[MAX_PATH] = { 0 };
    DWORD lpDataLength = MAX_DATA_LENGTH;;
    int k;

    long F = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",0, KEY_READ, &key);
    if (F == ERROR_SUCCESS)
        {
            while (RegEnumValue(key, dwIndex, lpValueName, &lpcchValueName, NULL, NULL, (LPBYTE)tcValue, &lpDataLength) == ERROR_SUCCESS)
            {
            cout<<"Program"<<k<<":"<<endl;
            cout<<lpValueName<<endl;
            cout<<tcValue<<endl;
            k++;
            lpDataLength = MAX_DATA_LENGTH;
            }
        }
    else
    {
        cout<< "Not program"<<endl;
    }
    RegCloseKey(key);
    cout<<" "<<endl;

    //2
    QueryPerformanceCounter(&t_1);
    QueryPerformanceFrequency(&fr);
    QueryPerformanceCounter(&t_2);


    double frequency = fr.QuadPart;
    double time = 1000000 * (t_2.QuadPart - t_1.QuadPart)/ frequency;

    cout<< "Frequency = "<< frequency << endl;
    cout<< "Time = " << time << endl;

    return 0;
}
