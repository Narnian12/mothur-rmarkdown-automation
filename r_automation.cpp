//
//  main.cpp
//  R_Analysis_Automation
//
//  Created by Peter Sun on 8/21/17.
//  Copyright © 2017 Peter Sun. All rights reserved.
//

#include <string>
#include <vector>
#include <fstream>

#include "pca_ra.h"

#include <iostream>

// cd Google\ Drive/MicroComp/R_Automation

void PCAGenerator(PCA_RA pcaRAObj_in, std::vector<std::string> colVec_in, std::string factorName);

int main() {
    std::string input;
    std::string title;
    std::string author;
    std::string date;
    std::string otuTable;
    std::string otuTax;
    std::vector<std::string> sampleVec;
    std::vector<std::pair<std::string, std::string>> varVec;
    std::vector<std::pair<std::string, std::string>> contVec;
    std::vector<std::string> colVec = {"blue", "red", "black", "orange", "green", "purple", "turquoise", "gray50"};

    std::cout << "Welcome to the R Automation Program! Here we will walk through the process of creating some RMarkdown commands.\n"
        << "Do you want to generate a list of your sample names? Type in <label> if so, otherwise type anything else "
        << "(make sure you have <DONE> at the end of your shared doc): ";

    std::cin >> input;
    if (input == "label") {
        std::cin >> input;
        while (input != "DONE") {
            if (input == "0.03") {
                std::cin >> input;
                sampleVec.push_back(input);
            }
            std::cin >> input;
        }
        for (auto x : sampleVec) {
            std::cout << x << "\n";
        }
    }

    else {
        // Title
        std::cout << "What is the title of your report? Please type <DONE> when you finish your title: ";
        std::cin >> input;
        title = input;
        std::cin >> input;
        while (input != "DONE") {
            title = title + " " + input;
            std::cin >> input;
        }
        // Debugging
        // std::cout << title << "\n";

        // Author
        std::cout << "Who is the author? Please write your name then type <DONE>: ";
        std::cin >> input;
        author = input;
        std::cin >> input;
        while (input != "DONE") {
            author = author + " " + input;
            std::cin >> input;
        }

        // Date
        std::cout << "When did you start the project? Please use the format <M/D/YYYY>: ";
        std::cin >> date;
        // Debugging
        // std::cout << "Date is " << date << "\n";

        // OTU Table
        std::cout << "\nWhat is the directory PATH to your otu table (.opti_mcc.shared)? Mine begins with </Desktop...>\n"
            << "TIP: You can drag the file to your terminal to see most of your PATH: ";
        // /Desktop/MicroComp/16s_huff_june/miseq.trim.contigs.good.unique.good.filter.unique.precluster.pick.pick.opti_mcc.shared
        std::cin >> otuTable;

        // OTU Taxonomy
        std::cout << "\nWhat is the directory PATH to your otu taxonomy table (.opti_mcc.0.03.cons.taxonomy)? Mine beigns with </Desktop...>\n"
            << "TIP: You can drag the file to your terminal to see most of your PATH: ";
        // /Desktop/MicroComp/16s_huff_june/miseq.trim.contigs.good.unique.good.filter.unique.precluster.pick.pick.opti_mcc.0.03.cons.taxonomy
        std::cin >> otuTax;

        std::cout << "\nNext enter in all the greps you want to do for the dataset. First input sample names, then type <CONTROLS> and "
            << "then enter your control names, and then enter <DONE> when finished: ";

        std::cin >> input;
        while (input != "CONTROLS") {
            std::string varString = input;
            // Removes the .*. within greps
            for (unsigned int i = 0; i < varString.size() - 2; ++i) {
                // std::cout << "substr is " << input.substr(i, 3) << "\n"; // DEBUG
                if (varString.substr(i, 3) == ".*.") {
                    varString.erase(i, 3);
                    break;
                }
            }
            // Removes __ into _
            for (unsigned int i = 0; i < varString.size() - 1; ++i) {
                if (varString.substr(i, 2) == "__") {
                    varString.erase(i, 1);
                    break;
                }
            }
            // Replaces caps into lowercase letters
            // std::cout << "varString now is " << varString << "\n"; // DEBUG
            for (unsigned int i = 0; i < varString.size(); ++i) {
                std::cout << "gg "; // DEBUG WTF
                if (varString[i] > 64 && varString[i] < 91) {
                    varString[i] = (varString[i] + 32);
                }
            }

            std::pair<std::string, std::string> pairVal (varString, input);

            varVec.push_back(pairVal);
            std::cin >> input;
        }
        std::cin >> input;
        while (input != "DONE") {
            std::string contString = input;
            // Removes the .*. within greps
            for (unsigned int i = 0; i < contString.size() - 2; ++i) {
                // std::cout << "substr is " << input.substr(i, 3) << "\n"; // DEBUG
                if (contString.substr(i, 3) == ".*.") {
                    contString.erase(i, 3);
                    break;
                }
            }
            // Removes __ into _
            for (unsigned int i = 0; i < contString.size() - 1; ++i) {
                if (contString.substr(i, 2) == "__") {
                    contString.erase(i, 1);
                    break;
                }
            }
            // Replaces caps into lowercase letters
            // std::cout << "input now is " << input << "\n"; // DEBUG
            for (unsigned int i = 0; i < contString.size(); ++i) {
                if (contString[i] > 64 && contString[i] < 91) {
                    contString[i] = (contString[i] + 32);
                }
            }

            std::pair<std::string, std::string> pairVal (contString, input);

            contVec.push_back(pairVal);
            std::cin >> input;
        }

        std::cout << "Here are your greps: ";
        for (auto x : varVec) {
            std::cout << x.first << " ";
        }
        for (auto x : contVec) {
            std::cout << x.first << " ";
        }

        std::cout << "\n\nHere are your variables: ";
        for (auto x : varVec) {
            std::cout << x.second << " ";
        }

        std::cout << "\n\nHere are your controls: ";
        for (auto x : contVec) {
            std::cout << x.second << " ";
        }

        std::cout << "\n\n\nBELOW we will detail the beginnings of the RMarkdown document that worked for me. "
            << "I used a Mac, but you can play around with the settings (margins, options, output, etc)."
            << "ALSO NOTE that I'm using PDF output, meaning you need to install LaTeX.\n\n\n";

        // RMARKDOWN BEGIN
        std::cout << "RMARKDOWN BEGIN\n~~~~~~~~~~~~~~~\n\n";

        std::cout << "---\ntitle: \"" << title << "\"\n"
            << "author: \"" << author << "\"\n"
            << "date: \"" << date << "\"\n"
            << "output:\n  pdf_document: default\n---\n---\n"
            << "geometry: margin = 1cm\n---\n\n";

        std::cout << "```{r global.options, include = FALSE}\n"
            << "knitr::opts_chunk$set(\n    cache = TRUE, # Caches results so knits go faster\n    "
            << "fig.align   = 'center', # Aligns graphics 'left' 'right' or 'center'\n    "
            << "warning = FALSE) # Won't display warnings in final doc\n```\n\n";

        std::cout << "```{r set-options, echo = FALSE}\n"
            << "options(width = 200)\n```\n\n";

        std::cout << "```{r include = FALSE}\n"
            << "# Add in necessary libraries and sem function\n"
            << "library(vegan)\nlibrary(mvabund)\nlibrary(gplots)\n"
            << "library(RColorBrewer)\nlibrary(MASS)\n\n"
            << "sem <- function(x) { sqrt(var(x, na.rm = TRUE) / length(na.omit(x))) }\n```\n\n";

        std::cout << "```{r include = FALSE}\n# Add in OTU tables and clean up\n"
            << "otu.raw <- read.table(\"~" << otuTable << "\", sep = \"\\t\", row.names = 2, header = T)\n"
            << "otu.trim <- otu.raw[, -c(1:2)]\n"
            << "rownames(otu.trim) <- sub(\"_S.*.\", \"\", rownames(otu.trim))\n"
            << "otu.trim <- as.matrix(otu.trim)\n"
            << "otu.tmp <- decostand(otu.trim, \"total\") * 100\n"
            << "neg1 <- which(otu.tmp < 0.5)\n"
            << "otu.trim[neg1] <- 0\n"
            << "pos <- which(colSums(otu.trim) > 0)\n"
            << "otu.good <- otu.trim[, pos]\n"
            << "otu.good.norm <- decostand(otu.good, \"total\") * 100\n```\n\n";

        std::cout << "```{r include = FALSE}\n"
            << "# Taxonomy table\n"
            << "tax1 <- read.table(\"~" << otuTax << "\", sep = \"\\t\", row.names = 1, header = T)\n"
            << "tax2 <- read.table(\"~" << otuTax << "\", sep = \";\", skip = 1)\n"
            << "otu.taxonomy <- cbind(tax1[,1],sub(\"\\\\(.*.\\\\)\",\"\","
            << "tax2[,2]),sub(\"\\\\(.*.\\\\)\",\"\","
            << "tax2[,3]),sub(\"\\\\(.*.\\\\)\",\"\","
            << "tax2[,4]),sub(\"\\\\(.*.\\\\)\",\"\","
            << "tax2[,5]),sub(\"\\\\(.*.\\\\)\",\"\","
            << "tax2[,6]))\n"
            << "rownames(otu.taxonomy) <- rownames(tax1)\n"
            << "colnames(otu.taxonomy) <- c(\"Size\", \"Phylum\", \"Class\", \"Order\", \"Family\", \"Genus\")\n"
            << "otu.good.taxonomy <- otu.taxonomy[colnames(otu.good), ]\n"
            << "otu.good.taxonomy <- as.data.frame(otu.good.taxonomy)\n```\n\n";

        std::cout << "```{r include = FALSE}\n"
            << "# Variable greps and order\n";
        for (auto x : varVec) {
            std::cout << x.first << " <- grep(\"" << x.second << "\", rownames(otu.good))\n"
                << x.first << ".order <- names(sort(colMeans(otu.good[" << x.first << ", ]), decreasing = T))\n";
        }
        std::cout << "# Control greps and order\n";
        for (auto x : contVec) {
            std::cout << x.first << " <- grep(\"" << x.second << "\", rownames(otu.good))\n"
                << x.first << ".order <- names(sort(colMeans(otu.good[" << x.first << ", ]), decreasing = T))\n";
        }
        std::cout << "```\n\n";

        std::cout << "# Control Analysis\n\n"
            << "We will look at various controls and how their abundant OTUs affect the samples.\n\n";

        for (auto x : contVec) {
            std::cout << "## " << x.second << " Controls\n\n"
                << "```{r echo = FALSE, fig.width = 12, fig.height = 6}\n";
            // Make an original order for the control
            std::cout << "par(mfrow = c(2, 1))\n"
                << "boxplot(otu.good.norm[" << x.first << ", " << x.first << ".order[1:50]],"
                << "las = 3, xaxt = 'n', main = \"Rank Abundance of " << x.second << " Signal\", ylab = \"%Relative Abundance\")\n\n";
            for (unsigned int i = 0; i < varVec.size(); ++i) {
                if (i < (varVec.size() - 1)) {
                    std::cout << "par(mfrow = c(2, 1))\n"
                        << "boxplot(otu.good.norm[" << varVec[i].first << ", " << x.first << ".order[1:50]],"
                        << "las = 3, xaxt = 'n', main = \"Rank Abundance of " << varVec[i].second
                        << " Ordered by " << x.second << " Signal\", ylab = \"% Relative Abundance\")\n\n";
                }
                // Last one
                else {
                    std::cout << "par(mfrow = c(2, 1))\n"
                        << "boxplot(otu.good.norm[" << varVec[i].first << ", " << x.first << ".order[1:50]],"
                        << "las = 3, names = paste(otu.good.taxonomy[" << x.first << ".order[1:50], 6], "
                        << "\"(\", " << x.first << ".order[1:50], \")\", sep = \"\"), "
                        << "main = \"Rank Abundance of " << varVec[i].second << " Ordered by "
                        << x.second << " Signal\", ylab = \"% Relative Abundance\")\n```\n\n";
                }
            }
        }

        std::cout << "\\newpage\n\n## PCA Analysis\n\n"
            << "```{r include = FALSE}\n# Removing controls from otu.good2\n" << "otu.good2 <- otu.good[-c(";
        for (unsigned int i = 0; i < contVec.size(); ++i) {
            if (i < contVec.size() - 1) {
                std::cout << contVec[i].first << ", ";
            }
            else {
                std::cout << contVec[i].first << "), ]\n";
                break;
            }
        }
        std::cout << "otu.good2.hel <- decostand(otu.good2, \"hellinger\")\n"
            << "otu.good2.pca <- rda(otu.good2.hel)\n" << "head(summary(otu.good2.pca))\n# PC1 ##.##%\n# PC2 ##.##%\n\n";

        // Variables for otu.good2
        std::cout << "```{r include = FALSE}\n"
            << "# Variable greps and order for PCA\n";
        for (auto x : varVec) {
            std::cout << x.first << "2" << " <- grep(\"" << x.second << "\", rownames(otu.good2))\n"
                << x.first << "2" << ".order <- names(sort(colMeans(otu.good2[" << x.first << ", ]), decreasing = T))\n";
        }

        // Generate PCA factor
        std::cout << "#General types primarily for PCA\n"
            << "gen.types <- character()\n";
        for (auto x : varVec) {
            // Here x.first indicates the location within gen.types and x.second indicates the show.groups name
            std::cout << "gen.types[" << x.first << "] <- \"" << x.second << "\"\n";
        }
        std::cout << "gen.types <- as.factor(gen.types)\n"
            << "gen.types.col <- c(";
        for (unsigned int i = 0; i < varVec.size(); ++i) {
            if (i != 0) {
                std::cout << ", \"" << colVec[i] << "\"";
            }
            else {
                std::cout << "\"" << colVec[i] << "\"";
            }
        }
        std::cout << ")\n";

        std::cout << "```\n\n";

        // First PCA Analysis
        std::cout << "```{r echo = FALSE, fig.width = 12, fig.height = 8}\n"
            << "plot(otu.good2.pca, type = \"n\", font = 2, font.lab = 2, xlab = \"PC1 (##.#% explained)\", "
            << "ylab = \"PC2 (##.#% explained)\", main = \"PCA by Type\")\n";
        // Points
        for (unsigned int i = 0; i < varVec.size(); ++i) {
            std::cout << "points(otu.good2.pca, pch = 19, select = " << varVec[i].first << "2, col = \"" << colVec[i] << "\", cex = 0.7)\n";
        }

        // Ordispider
        for (unsigned int i = 0; i < varVec.size(); ++i) {
            std::cout << "ordispider(otu.good2.pca, display = \"sites\", gen.types, label = T, show.groups = \""
                << varVec[i].second << "\", col = \"" << colVec[i] << "\")\n";
        }

        // Legend
        std::cout << "legend(\"bottomright\", c(";
        for (unsigned int i = 0; i < varVec.size(); ++i) {
            if (i > 0) {
                std::cout << ", \"" << varVec[i].second << "\"";
            }
            else {
                std::cout << "\"" << varVec[i].second << "\"";
            }
        }
        std::cout << "))\n```\n\n";

        // Finish this section of RMarkdown
        std::cout << "~~~~~~~~~~~~~\nRMARKDOWN END\n\n\n";

        std::cout << "We will now delve deeper into PCA and Rank Abundances for various groups. It will be ordered first PCA, then RA\n\n";

        // std::vector<PCA_RA> pcaRAVec;
        char yesNo;

        while (input != "PCA_RA_DONE") {
            std::cout << "Do you want to perform PCA and RA analyses? Type <Y> for yes, <N> for no: ";
            std::cin >> yesNo;
            if (yesNo == 'N') {
                break;
            }
            // PCA and RA Analysis
            PCA_RA pcaRAObj;

            std::cout << "What is/are the variable name(s) you want to perform PCA on? The variable names MUST come from below:\n";
            int incr = 0;
            for (auto x : varVec) {
                std::cout << x.first << " " << incr << "\n";
                ++incr;
            }
            std::cout << "\nType in the INDEX NUMBER(S) of the variable(s). Type <-1> when finished: ";
            std::pair<std::string, std::string> pcaRAObjPair;
            std::cin >> incr;
            while (incr != -1) {
                pcaRAObjPair.first = varVec[incr].first;
                pcaRAObjPair.second = varVec[incr].second;
                pcaRAObj.pcaVec.push_back(pcaRAObjPair);
                std::cin >> incr;
            }
            std::cout << "Now type in the REST OF THE INDECES you did not use. For example, if there were indeces 0-5 in the beginning and you are doing PCA on 1, 2 and 3, type 0 4 5 -1: ";
            std::cin >> incr;
            while (incr != -1) {
                pcaRAObj.otuRmVec.push_back(varVec[incr].first);
                std::cin >> incr;
            }
            // RA Analysis
            std::cout << "Do you want to perform RA Analysis? Enter <Y> for yes, <N> for no: ";
            std::cin >> yesNo;
            if (yesNo == 'N') {
                continue;
            }
            // Read in sample that will be order throughout entire RA
            std::cout << "\nWhat is the sample you want to order every other sample against? " 
                << "If not (you want to order samples by themselves), type <NONE>: ";
            std::cin >> input;
            pcaRAObj.raMainString = input;
            // Read in RA samples
            std::cout << "\nWhat are the samples you want to perform RA on? Type <DONE> when done: ";
            std::cin >> input;
            while (input != "DONE") {
                pcaRAObj.raVec.push_back(input);
                std::cin >> input;
            }

            // Output PCA and RA
            std::cout << "What do you want your factor for the ";
            for (auto x : pcaRAObj.pcaVec) {
                std::cout << "\"" << x.second << "\" ";
            }
            std::cout << "group to be called? Please type a variable name that hasn't been used and doesn't have any spaces: ";
            std::cin >> input;

            PCAGenerator(pcaRAObj, colVec, input);


            // Repeat while loop
            std::cout << "If you don't want to continue anymore, type <PCA_RA_DONE>, otherwise type anything else: ";
            std::cin >> input;
        }

        std::cout << "SUCCESS!\n";
    }
    return 0;
}


void PCAGenerator(PCA_RA pcaRAObj_in, std::vector<std::string> colVec_in, std::string factorName) {
    std::cout << "```{r include = FALSE}\n";
    std::cout << "otu.good2." << factorName << "<- otu.good2[-c(\n";
    // Remove these variables from this particular otu.good2.factorName
    for (unsigned int i = 0; i < pcaRAObj_in.otuRmVec.size(); ++i) {
        if (i > 0) {
            std::cout << ", " << pcaRAObj_in.otuRmVec[i];
        }
        else {
            std::cout << pcaRAObj_in.otuRmVec[i];
        }
    }
    std::cout << "), ]\n";
    // Create hellinger and .pca here
    std::cout << "otu.good2." << factorName << "hel <- decostand(otu.good2." << factorName << ", \"hellinger\")\n"
        << "otu.good2." << factorName << ".pca <- rda(otu.good2." << factorName << "hel)\n"
        << "head(summary(otu.good2." << factorName << ".pca))\n"
        << "# PC1 ##.##%\n# PC2 ##.##%\n```\n\n";

    // Create variables specific to this OTU
    for (auto x : pcaRAObj_in.pcaVec) {
        std::cout << x.first << "." << factorName << " <- grep(\"" << x.second << "\", rownames(otu.good2." << factorName << "))\n";
    }

    // Create factor
    std::cout << "#Factor for type\n" << factorName << "<- character()\n";
    for (auto x : pcaRAObj_in.pcaVec) {
        // Variable name is x.first + 2 + factorName
        std::cout << factorName << "[" << x.first << "2'" << factorName << "] <- \"" << x.second << "\"\n";
    }
    std::cout << factorName << "<- as.factor(" << factorName << ")\n";
    // Factor cols
    std::cout << "type.cols <- c(";
    for (unsigned int i = 0; i < pcaRAObj_in.pcaVec.size(); ++i) {
        if (i > 0) {
            std::cout << ", " << colVec_in[i];
        }
        else {
            std::cout << "\"" << colVec_in[i] << "\"";
        }
    }
    std::cout << ")\n```\n\n";

    std::cout << "```{r echo = FALSE, fig.width = 12, fig.height = 8}\n";
    // Points
    for (unsigned int i = 0; i < pcaRAObj_in.pcaVec.size(); ++i) {
        // Replicate variable name x.first + 2 + factorName
        std::cout << "plot(otu.good2." << factorName << ".pca, pch = 19, select = " << pcaRAObj_in.pcaVec[i].first
            << "2" << factorName << ", col = \"" << colVec_in[i] << "\")\n";
    }

    // Ordispider
    for (unsigned int i = 0; i < pcaRAObj_in.pcaVec.size(); ++i) {
        std::cout << "ordispider(otu.good2." << factorName << ".pca, display = \"sites\", " << factorName << ", label = T, show.groups = ";
    }

    std::cout << "STILL GOING";
}


















