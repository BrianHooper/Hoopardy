function showz(card) {
    var t = card.querySelector(".button-points-text");
    t.classList.toggle("button-points-faded");

    t.classList.add("button-price-text-hidden");
    t.classList.remove("button-price-text-visible");
    var s = card.parentNode.querySelector(".question-card");
    s.classList = ["question-card question-card-visible"];
}

function hide(card) {
    card.classList.remove('question-card-visible');
    card.classList.add('question-card-hidden');
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
  
  // Your validation function
  function validate(e) {
    alert("enter");
  }