#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define pb push_back
#define mp make_pair
#define fi first
#define sec second
typedef long long ll;
typedef long double  ld;
#define pii pair<ll,ll>
#define vi vector< ll >
#define vvi vector< vi >
#define vpi vector< pii >
#define vvpi vector< vpi >
#define test(t) ll t;cin>>t;while(t--)
#define mem(a,b) memset(a,b,sizeof(a))
#define inn freopen("input.txt", "r", stdin)
#define outt freopen("output.txt", "w", stdout)
#define all(arr) arr.begin(),arr.end()
#define fr(i,n) for(ll i=0;i<(n);++i)
#define rep(i,a,b) for(ll i=a;i<=b;++i)
#define per(i,a,b) for(ll i=a;i>=b;i--)
#define remin(a,b) (a=min((a),(b)))
#define remax(a,b) (a=max((a),(b)))

struct skill {
    string skillName;
    ll level;
};

struct developer {
    string name;
    ll numberOfSkills;
    bool allocated;
    vector <skill> skills;
};

struct project {
    string name;
    ll D; // variable for number of days
    ll S; // variable for score
    ll B; // Best before day
    ll R; // number of roles
    
    ll feasibilityScore; // feasibility score

    vector <skill> skills;
};
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}


bool sortBestProjects(project p1, project p2){
    return p1.feasibilityScore<p2.feasibilityScore;
}   

struct outputStructure {
    string name;
    vector <string> developers;
};

void sol(){
    ll c,p; // number of contributors and projects
    cin>>c>>p;
    vector <developer> contributors(c); // vector for contributors
    vector <project> projects(p); // vector for projects
    vector <outputStructure> outputkliye;

    fr(i,c) {
        string contributorName;
        cin>>contributorName;
        ll numberOfSkills;
        cin>>numberOfSkills;

        developer tempDeveloper;

        tempDeveloper.name = contributorName;
        tempDeveloper.numberOfSkills = numberOfSkills;
        tempDeveloper.allocated = false;

        fr(j,numberOfSkills){
            string skillName;
            cin>>skillName;
            ll skillLevel;
            cin>>skillLevel;

            skill tempSkill;

            tempSkill.skillName = skillName;
            tempSkill.level = skillLevel;

            tempDeveloper.skills.pb(tempSkill);
        }

        contributors[i] = tempDeveloper;
    }


    fr(i,p){
        string projectName;
        cin>>projectName;
        ll numberOfDays;
        cin>>numberOfDays;
        ll projectScore;
        cin>>projectScore;
        ll bestBeforeDay;
        cin>>bestBeforeDay;
        ll numberOfRoles;
        cin>>numberOfRoles;

        project tempProject;

        tempProject.name = projectName;
        tempProject.D = numberOfDays;
        tempProject.S = projectScore;
        tempProject.B = bestBeforeDay;
        tempProject.R = numberOfRoles;
        // tempProject.feasibilityScore = projectScore/numberOfDays;
        tempProject.feasibilityScore = numberOfRoles;

        fr(j,numberOfRoles){
            string skillName;
            cin>>skillName;
            ll level;
            cin>>level;

            skill tempSkill;

            tempSkill.skillName = skillName;
            tempSkill.level = level;

            tempProject.skills.pb(tempSkill);

        }

        projects[i] = tempProject;
    }

    // ALGORITHM STARTS HERE

    sort(all(projects),sortBestProjects);

    // ORDER OF PROJECTS
    // for(auto i:projects){
    //     cout<<i.name<<"\n";
    // }

    // cout<<p<<"\n";
    ll completedProjects = p;

    fr(i,p){
        // cout<<projects[i].name<<"\n";

        vector <string> developersContributed;

        fr(j,projects[i].R){
            // cout<<"SKILL REQ: "<<projects[i].skills[j].skillName<<" "<<projects[i].skills[j].level<<"\n";

            string requiredSkillName = projects[i].skills[j].skillName;
            ll requiredSkillLevel = projects[i].skills[j].level;

            ll indexOfBestContributor = 0;
            string bestSol = "";
            ll bestSkill = 0;

            bool milgya = false;

            fr(k,c){

                vector <skill> skillOfContributor = contributors[k].skills;

                fr(l,contributors[k].numberOfSkills){

                    if(contributors[k].skills[l].skillName == requiredSkillName && 
                        contributors[k].skills[l].level >= requiredSkillLevel
                        && contributors[k].allocated != true){

                            // cout<<contributors[k].name<<" ";
                            developersContributed.pb(contributors[k].name);
                            contributors[k].allocated=true;
                            milgya = true;
                            break;

                    }
                }
                if(milgya) break;
            } 
        }

        if(developersContributed.size()>0 && developersContributed.size() == projects[i].R){
            outputStructure tempOutput;
            
            tempOutput.name = projects[i].name;

            // cout<<projects[i].name<<"\n";
            for(auto dev:developersContributed){
                tempOutput.developers.pb(dev);
            }

            outputkliye.pb(tempOutput);
            // cout<<"\n";
        }else{
            completedProjects--;
        }

        fr(j,c){
            contributors[j].allocated = false;
        }
    }

    cout<<completedProjects<<"\n";

    ll numberOfOutputs = outputkliye.size();

    fr(i,numberOfOutputs){

        cout<<outputkliye[i].name<<"\n";
        for(auto dev:outputkliye[i].developers) cout<<dev<<" ";
        cout<<"\n";
    }

}

int main(int argc, char **argv){
    string inputFile = "input/"+(string)argv[1];
    string outputFile = "output/output-"+(string)argv[1];
    freopen(inputFile.c_str(), "r", stdin);
    freopen(outputFile.c_str(), "w", stdout);
    sol();
    return 0;
}