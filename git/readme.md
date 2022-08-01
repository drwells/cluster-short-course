# Module 2: git

## Preliminaries
* Suppose your thesis advisor doesn't like using computers and hands you paper
  revisions done in pen. Concurrently, your collaborators edit the manuscript to
  make a related set of changes. How can you resolve both rounds of edits and
  make sure nothing gets lost?
* Suppose you are writing a computer program with another student. Before you
  make changes, you want to be able to propose and review them. What's the best
  way to keep concurrent changes neatly organized so you know who is doing what?

The answer to both is 'use a version control system' (VCS) (sometimes also
called a revision control system). Algorithms for tracking line-by-line changes
to text are pretty good these days - version control systems understand how to
efficiently track changes to projects.

We will use `git`, the "stupid content tracker". `git` is by far the most
popular version control software in use today (and for the last decade or so).
Some alternatives are:
* mercurial: written in python, easy to understand, historically was able to
  handle truly massive projects (e.g., all the code at facebook is managed with
  mercurial repository)
* fossil: provides some extra integrity guarantees
* SVN: previously (until 2010 or so) the most popular version control system.

## Using git

### `git` is distributed
`git` is a *distributed* version control system, meaning that when we clone a
repository we have all the files and all the history locally. Try cloning this very repository at the command line with

```
git clone https://github.com/drwells/cluster-short-course
cd cluster-short-course
git log
```

When was this course material written?

### `git` allows concurrency
Lets take a look at what is going on in deal.II these days as an example of
how people use `git` in practice to make and review changes.

The approach we will highlight in this course is called *feature branches*: at
any given point in deal.II, all changes to the `master` branch have been
peer-reviewed and tested.

### Making changes to this repository
To practice (I will undo it later) lets make changes to this repository based on
the completed shell scripts in module 1.

#### Setting things up
To start, make sure your contact information is set up:
```
git config --local user.name "My Name"
git config --local user.email "My email"
```

#### Create a GitHub account
GitHub is an online platform which allows us to look at `git` repositories and
manipulate them. There are plenty of competitors these days (like GitLab) but
GitHub is the oldest and biggest.

Make a GitHub account so that we can put your changes in my repository!

#### Set things up locally
1. Start by 'forking' my repository on the GitHub web page.
2. The clone you made on your machine needs to be updated to know about your
   fork: take a look at the file `.git/config`. It should look something like
   this:
```
[core]
	repositoryformatversion = 0
	filemode = true
	bare = false
	logallrefupdates = true
[user]
	name = David Wells
	email = drwells@email.unc.edu
[remote "origin"]
	url = git@github.com:drwells/cluster-short-course.git
	fetch = +refs/heads/*:refs/remotes/origin/*
[branch "master"]
	remote = origin
	merge = refs/heads/master
```
   To meet the standard convention, copy and paste `origin` and make it point to
   your git repository and then rename the original (mine) to `upstream`. This
   way your local copy knows about two other relevant clones: yours and mine on
   GitHub.

#### Add some changes
1. Create a branch with
```
git checkout update-script-X
```
in which `X` is the script number you are changing.
2. When you type
```
git status
```
   what do you see? Does this make sense?
3. Add the changes you have made with `git add`. This stages changes.
4. Commit the changes with `git commit -m "message"`: be sure to write a terse
   but useful commit message.

#### Moving things to GitHub
Remember, this local fork is not automatically synchronized with anything on
GitHub: you need to create a branch on GitHub to match the one on your machine with
```
git push origin update-script-X
```
Now we can use GitHub's interface to review and update the code! Open a pull request.

#### Code Review
For the sake of practice I'll ask for changes. To keep the history tidy you can try any of the following things to combine commits:
```
git commit --amend
git reset --soft HEAD~1 && git add script-X.sh && git commit -m "message"
git add script-X.sh && git commit -m "message" && git rebase -i master
```
These all accomplish the same thing in three different ways:
1. Amend the current commit with new changes.
2. Undo the current commit, add your changes, and create a new commit. When you
   do a soft reset the changes on the current commit (here `HEAD~1`, meaning the
   last commit) are still staged but the commit is no longer in the history. At
   this point everything you need is staged so you can create a new commit.
3. Interactively rebase - this is the most complex and flexible option and it
   allows you to rebase (meaning put all your commits after, in this case, the
   `master` branch and possibly delete, combine, or edit them).

We aren't going to be able to learn everything about `git` in this workshop but
its important that you see that it is a very powerful system that can help you
keep a tidy set of changes. One of my favorite git features is the "octopus
merge" in which multiple branches are simultaneously combined into a single
branch (I believe GitHub's mascot, octocat, comes from the name of this
technique)

#### Staying up-to-date
Once everyone merges their code, you should switch back to `master` and update
your local changes accordingly:
```
git checkout master
git pull upstream master
```
If this doesn't work (e.g., if you accidentally committed things onto the master
branch) then we will have to manually intervene.
