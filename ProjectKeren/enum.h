#pragma once

enum menu {
    AddCounty = 1,
    AddCitizen = 2,
    AddParty = 3,
    SetRepresentative = 4,
    DisplayCounties = 5,
    DisplayCitizens = 6,
    DisplayParties = 7,
    SetVote = 8,
    DisplayElectionResult = 9,
    Exit = 10,
    SaveElection = 11,
    LoadElection = 12,

    regularElection = 1,
    simpleElection = 2,
    unifiedCounty = 1,
    dividedCounty = 2,
    CreateNewElection = 1,
    LoadFromFile = 2
};