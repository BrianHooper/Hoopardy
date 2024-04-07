function showz(card) {
    var t = card.querySelector(".button-points-text");
    t.classList.toggle("button-points-faded");

    var s = card.parentNode.querySelector(".clue");
    s.classList.add("question-card-visible");
}

function showquestion(card) {
    var questionCard = card.querySelector(".clue");
    console.log(questionCard);
    questionCard.classList.add("question-card-visible");

    var button = card.querySelector(".button-points");
    button.classList.toggle("button-points-faded");
}

function hidecard(card) {
    var questionCard = card.querySelector(".clue");
    if (questionCard) {
        questionCard.classList.remove("question-card-visible");
    }

    var answerCard = card.querySelector(".answer");
    if (answerCard) {
        answerCard.classList.remove("question-card-visible");
    }
}

function hide(card) {
    const parent = card.parentNode;
    parent.classList.remove("question-card-visible");
}

function showanswer(card) {
    var questionCard = card.querySelector(".clue");
    if (questionCard) {
        questionCard.classList.remove("question-card-visible");
    }

    var answerCard = card.querySelector(".answer");
    if (answerCard) {
        answerCard.classList.add("question-card-visible");
    }
}

function editname(card) {
    const nameElem = card.querySelector(".score-name");
    const existingName = nameElem.innerText;
    const teamName = prompt("Team name", existingName);
    nameElem.innerText = teamName;
}

function addpoints(card) {
    const parent = card.parentNode;
    const pointsElem = parent.querySelector(".score-points");
    addpointsdirect(pointsElem);
}

function rempoints(card) {
    const parent = card.parentNode;
    const pointsElem = parent.querySelector(".score-points");
    let existingPoints = Number(pointsElem.innerText);
    existingPoints -= 200;
    if (existingPoints >= 0) {
        pointsElem.innerText = existingPoints;
    }
}

function rempointsdirect(card) {
    let existingPoints = Number(card.innerText);
    existingPoints -= 200;
    if (existingPoints >= 0) {
        card.innerText = existingPoints;
    }
}

function addpointsdirect(card) {
    let existingPoints = Number(card.innerText);
    existingPoints += 200;
    card.innerText = existingPoints;
}

function remstartcard() {
    const card = document.querySelector("#start-overlay");
    card.style.visibility = "hidden";
}

document.addEventListener("keydown", function (e) {
    if (e.code === "Enter") {
      remstartcard();
    } else if (e.code === "Digit1") {
        rempointsdirect(document.querySelector("#score-points-1"));
    } else if (e.code === "Digit2") {
        addpointsdirect(document.querySelector("#score-points-1"));
    } else if (e.code === "Digit3") {
        rempointsdirect(document.querySelector("#score-points-2"));
    } else if (e.code === "Digit4") {
        addpointsdirect(document.querySelector("#score-points-2"));
    } else if (e.code === "Digit5") {
        rempointsdirect(document.querySelector("#score-points-3"));
    } else if (e.code === "Digit6") {
        addpointsdirect(document.querySelector("#score-points-3"));
    } else if (e.code === "Digit7") {
        rempointsdirect(document.querySelector("#score-points-4"));
    } else if (e.code === "Digit8") {
        addpointsdirect(document.querySelector("#score-points-4"));
    }
  });

document.querySelectorAll(".points-box").forEach(function(card) {
    const qId = card.id;
    const pointsButton = card.querySelector(".button-points");
    pointsButton.addEventListener("click", function(){
        showquestion(card);
    }, false);
    
    const closeButtons = card.querySelectorAll(".close-button");
    if (closeButtons) {
        closeButtons.forEach(function(button) {
            button.addEventListener("click", function(){
                hidecard(card);
            }, false);
        });
    }

    const answerButton = card.querySelector(".answer-button");
    if (answerButton) {
        answerButton.addEventListener("click", function(){
            showanswer(card);
        }, false);
    }
});